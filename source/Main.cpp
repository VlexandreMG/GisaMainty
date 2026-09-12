#include <3ds.h>
#include <citro2d.h>
#include <stdio.h>
#include "../data/include/Goose.hpp"
#include "../data/manager/GooseManager.hpp"
#include "../data/system/System.hpp"

int main() {
    // 1. Initialisation matérielle
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    consoleInit(GFX_BOTTOM, NULL);

    // 2. Définition des cibles de rendu (Haut et Bas via Citro2D)
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    // C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    // 3. Création des deux oies
    GooseManager gm;
    System system;
    Goose* goose = gm.spawnGoose(180.0f, 100.0f);
    Goose* other = gm.spawnGoose(200.0f, 120.0f);

    // 4. Boucle Principale de Jeu (Gameloop)
    while (aptMainLoop()) {
        // --- A. INPUTS ---
        hidScanInput();
        u32 kdown = hidKeysDown();
        u32 kheld = hidKeysHeld();
        if (kdown & KEY_START) break; // Quitter le jeu avec START
        
        if (kheld & KEY_DRIGHT) {
            goose->mooveRight();
        }
        
        if (kheld & KEY_DLEFT) {
            goose->mooveLeft();
        }
        
        if (kheld & KEY_B) {
            goose->fly();
        }
        
        if (kdown & KEY_A) {
            goose->attack(); // Déclenche le déplacement de l'attaque
        }
        
        // --- B. UPDATE ---
        system.applyPhysics(gm.geese);
        gm.updateAll();
        goose->tryAttack(*other);
        goose->rightBound();
        goose->leftBound();
        goose->upBound();

        printf("\x1b[1;1H"); // Replace le curseur en haut à gauche
        printf("=== DEBUG GOOSE JETPACK ===\n\n");
        printf("Position Y   : %f\n", goose->y);
        printf("Vitesse VY   : %f\n", goose->vy);
        printf("Gaz Restant  : %f\n", goose->gas);
        printf("isGrounded   : %s\n", goose->isGrounded ? "TRUE " : "FALSE");
        printf("Bouton B     : %s\n", (kheld & KEY_B) ? "APPUYE " : "RELACHE");

        // --- C. RENDU GRAPHIQUE ---
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        // 1. ÉCRAN DU HAUT : Dessin des Oies
        C2D_TargetClear(top, C2D_Color32(250, 89, 21, 255)); // Fond Orange
        C2D_SceneBegin(top);
        
        // Dessin de l'oie Joueur (Rouge)
        for (Goose* gisa : gm.geese) {
            C2D_DrawRectangle(gisa->x, gisa->y, 0.0f, gisa->w, gisa->h, C2D_Color32(255, 0, 0, 255), C2D_Color32(255, 0, 0, 255), C2D_Color32(255, 0, 0, 255), C2D_Color32(255, 0, 0, 255));
        }

        // C2D_SceneBegin(bottom);
        // // 2. ÉCRAN DU BAS : Témoin visuel de Collision
        // if (other.health != 3) {
        //     // COLLISION ! L'écran du bas s'allume en BLANC
        //     C2D_TargetClear(bottom, C2D_Color32(255, 255, 255, 255));
        // } else {
        //     // Pas de collision : L'écran du bas reste BLEU FONCÉ
        //     C2D_TargetClear(bottom, C2D_Color32(20, 20, 80, 255));
        // }

        C3D_FrameEnd(0);
    }

    // 5. Nettoyage de la mémoire avant de quitter
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    gm.clear();
    return 0;
}