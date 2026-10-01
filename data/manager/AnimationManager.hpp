#include "../include/Animation.hh"
#include <citro2d.h>

class AnimationManager {
public:
    int frameCounter = 0;
    int tickTimer = 0;

    AnimationManager() : frameCounter(0), tickTimer(0) {}

    void updateAnimation(const Animation& anim) {
        tickTimer++;

        if (tickTimer >= anim.tickIncrementer) {
            frameCounter++;
            tickTimer = 0;
        }
    }

    void drawImageWithAnimation(C2D_SpriteSheet sheet , const Animation& anim,float x, float y) {
        // Boucle pour enchainer les images 
        int spriteIndex = anim.startFrame + (frameCounter % anim.totalFrames);

        // Pour getter l'image du sprite Sheet 
        C2D_Image image = C2D_SpriteSheetGetImage(sheet, spriteIndex);

        // Dessin de l'image 
        C2D_DrawImageAt(image, x, y, 0.9f, nullptr, 1.0f, 1.0f);
    }
};