#include <3ds.h>
#include <citro2d.h>
#include "../data/include/Goose.hpp"

int main() {
// Reveiller l'écran 
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();


// Où je dois dessiner 
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

// Création d'une oie 
    Goose goose = {200.0f,120.0f};

// Gameloop 
    while (aptMainLoop()) {
        hidScanInput();
        u32 kdown = hidKeysDown();
         if (kdown & KEY_START) break;

         // Frame à 60s
         C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
         C2D_TargetClear(top, C2D_Color32(250, 89, 21, 255));
         C2D_SceneBegin(top);
         
        C2D_DrawRectSolid(goose.x, goose.y, 0.0f, 15.0f, 15.0f, C2D_Color32(255, 0, 0, 255));

        C3D_FrameEnd(0);
    }
        
// Libération de mémoire 
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}