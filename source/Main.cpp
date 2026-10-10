#include <3ds.h>
#include <citro2d.h>
#include <stdio.h>
#include "../data/include/Goose.hpp"
#include "../data/manager/GooseManager.hpp"
#include "../data/manager/AnimationManager.hpp"
#include "../data/system/System.hpp"

int main() {
    // 1. Initialisation matérielle
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    romfsInit();

    consoleInit(GFX_BOTTOM, NULL);

    // 2. Définition des cibles de rendu (Haut et Bas via Citro2D)
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    // C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    // Charger la feuille de sprite 
    C2D_SpriteSheet sheetRight = C2D_SpriteSheetLoad("romfs:/gfx/Goose-walk-right.t3x");
    C2D_SpriteSheet sheetLeft = C2D_SpriteSheetLoad("romfs:/gfx/Goose-walk-left.t3x");
    // C2D_SpriteSheet sheetAttackRight = C2D_SpriteSheetLoad("romfs:/gfx/Goose-attack-right.t3x");
    
    //  ETO

    // De la droite ou de la gauche 
        bool facingRight = true;

    // Ne bouge pas     

     
    // Animation d'attaque 
    // Animation attack;
    // attack.totalFrames = 4;  
    // attack.startFrame =1 ;  
    // attack.tickIncrementer = 8; 

    // Animation de marche 
    Animation walk;
    walk.totalFrames = 4;  
    walk.startFrame =1 ;  
    walk.tickIncrementer = 8; 
    
    // Animation Manager 
    AnimationManager aM;
    
    // 3. Création des deux oies
    GooseManager gm;
    System system;
    Goose* goose = gm.spawnGoose(180.0f, 100.0f);
    Goose* other = gm.spawnGoose(200.0f, 120.0f);
    
    // Ne bouge pas 
    bool isMooving = aM.gooseIsMooving(goose);

    // 4. Boucle Principale de Jeu (Gameloop)
    while (aptMainLoop()) {
        // --- A. INPUTS ---
        hidScanInput();
        u32 kdown = hidKeysDown();
        u32 kheld = hidKeysHeld();
        if (kdown & KEY_START) break; // Quitter le jeu avec START

        if (kheld & KEY_DRIGHT) {
            goose->mooveRight();
            facingRight = true;
        } else if (kheld & KEY_DLEFT) { 
            goose->mooveLeft();
            facingRight = false;
        }   
        
        if (kheld & KEY_B) {
            goose->fly();
        }
        
        if (kdown & KEY_A) {
            goose->attack(); // Déclenche le déplacement de l'attaque
            // isAttacking = true;
        }
        
        // --- B. UPDATE ---
        system.applyPhysics(gm.geese);
        gm.updateAll();
        goose->tryAttack(*other);
        goose->rightBound();
        goose->leftBound();
        goose->upBound();
        
        // --- C. RENDU GRAPHIQUE ---
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_TargetClear(top, C2D_Color32(250, 89, 21, 255)); // Fond Orange
        C2D_SceneBegin(top);
        
        C2D_SpriteSheet currentSheet = facingRight ? sheetRight : sheetLeft;

        aM.fonctionTsisyAnarana(currentSheet,walk,isMooving,goose->x,goose->y);

        C3D_FrameEnd(0);
    }

    // 5. Nettoyage de la mémoire avant de quitter
    gm.clear();
    C2D_SpriteSheetFree(sheetLeft);
    C2D_SpriteSheetFree(sheetRight);
    romfsExit();
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}