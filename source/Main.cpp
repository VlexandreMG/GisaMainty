#include <3ds.h>
#include <citro2d.h>
#include "../data/include/Goose.hpp"
#include "../data/system/System.hpp"

int main() {
    // 1. Initialisation matérielle
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    // 2. Définition des cibles de rendu (Haut et Bas via Citro2D)
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    // 3. Création des deux oies
    Goose goose = {180.0f, 120.0f};
    Goose other = {190.0f, 120.0f}; // Oie Cible (Bleu) - Placée très proche pour tester facilement
    System system;

    // 4. Boucle Principale de Jeu (Gameloop)
    while (aptMainLoop()) {
        // --- A. INPUTS ---
        hidScanInput();
        u32 kdown = hidKeysDown();
        if (kdown & KEY_START) break; // Quitter le jeu avec START

        system.applyPhysics(goose);

        if (kdown & KEY_A) {
            goose.attack(); // Déclenche le déplacement de l'attaque
        }

        // --- B. UPDATE ---
        goose.update();
        goose.tryAttack(other);

        // --- C. RENDU GRAPHIQUE ---
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        // 1. ÉCRAN DU HAUT : Dessin des Oies
        C2D_TargetClear(top, C2D_Color32(250, 89, 21, 255)); // Fond Orange
        C2D_SceneBegin(top);
        
        // Dessin de l'oie Joueur (Rouge)
        C2D_DrawRectSolid(goose.x, goose.y, 0.0f, goose.w, goose.h, C2D_Color32(255, 0, 0, 255));
        
        // Dessin de l'oie Cible (Bleu)
        C2D_DrawRectSolid(other.x, other.y, 0.0f, other.w, other.h, C2D_Color32(0, 0, 255, 255));

        C2D_SceneBegin(bottom);
        // 2. ÉCRAN DU BAS : Témoin visuel de Collision
        if (other.health != 3) {
            // COLLISION ! L'écran du bas s'allume en BLANC
            C2D_TargetClear(bottom, C2D_Color32(255, 255, 255, 255));
        } else {
            // Pas de collision : L'écran du bas reste BLEU FONCÉ
            C2D_TargetClear(bottom, C2D_Color32(20, 20, 80, 255));
        }

        C3D_FrameEnd(0);
    }

    // 5. Nettoyage de la mémoire avant de quitter
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}