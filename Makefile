# ---------------------------------------------------------------------------------
# Configuration de l'environnement devkitPro
# ---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Veuillez définir DEVKITARM dans votre environnement : export DEVKITARM=/opt/devkitpro/devkitARM")
endif

include $(DEVKITARM)/3ds_rules

# ---------------------------------------------------------------------------------
# Informations sur le projet
# ---------------------------------------------------------------------------------
TARGET          := GisaMainty
BUILD           := build
SOURCES         := source
INCLUDES        := include include/manager include/system
GRAPHICS        := data/assets/gfx
ROMFS           := romfs

# ---------------------------------------------------------------------------------
# Drapeaux de compilation et dépendances
# ---------------------------------------------------------------------------------
ARCH            := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

LIBDIRS         := $(CTRULIB) $(PORTLIBS)
LIBPATHS        := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)
LIBS            := -lcitro2d -lcitro3d -lctru -lm

# ---------------------------------------------------------------------------------
# Logique récursive de compilation
# ---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT   := $(CURDIR)/$(TARGET)
export VPATH    := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
                   $(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir))
export DEPSDIR  := $(CURDIR)/$(BUILD)

CFILES          := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES        := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))

export OFILES   := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)

# Construction des dossiers d'inclusions (-I)
export INCLUDE  := $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
                   $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
                   -I$(CURDIR)/$(BUILD)

# Drapeaux de compilation C/C++
export CFLAGS   := -g -Wall -O2 -mword-relocations $(ARCH) $(INCLUDE)
export CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions

# LDFLAGS contient à la fois l'architecture et les specs 3DSX
export LDFLAGS  := $(ARCH) -specs=3dsx.specs $(LIBPATHS) -Wl,-Map,$(OUTPUT).map

# Intégration automatique du dossier RomFS s'il existe
ifneq ($(wildcard $(ROMFS)),)
    export APP_ROMFS := $(CURDIR)/$(ROMFS)
endif

.PHONY: $(BUILD) clean all

all: $(BUILD)

$(BUILD):
	@mkdir -p $@
	@$(MAKE) --no-print-directory -C $@ -f $(CURDIR)/Makefile

clean:
	@echo "Nettoyage..."
	@rm -rf $(BUILD) $(TARGET).3dsx $(TARGET).smdh $(TARGET).elf $(TARGET).map

else

# ---------------------------------------------------------------------------------
# Phase de compilation interne (depuis build/)
# ---------------------------------------------------------------------------------
DEPENDS := $(OFILES:.o=.d)

all: $(OUTPUT).3dsx

# Génération automatique 3DSX / ELF par les règles de 3ds_rules
$(OUTPUT).3dsx: $(OUTPUT).elf

$(OUTPUT).elf: $(OFILES)
	@echo "Linking $(notdir $@)..."
	@$(CXX) $(LDFLAGS) $(OFILES) $(LIBS) -o $@

-include $(DEPENDS)

endif