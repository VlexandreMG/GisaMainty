#include "../include/Animation.hh"
#include "../include/Goose.hpp"
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

    void resetAnimation() {
        frameCounter = 0;
        tickTimer = 0;
    }

    void idleAnimation(C2D_SpriteSheet sheet, float x , float y) {
        resetAnimation();
        C2D_Image image = C2D_SpriteSheetGetImage(sheet, frameCounter);
        C2D_DrawImageAt(image, x, y, 0.9f, nullptr, 1.0f, 1.0f);
    }

    void drawImageWithAnimation(C2D_SpriteSheet sheet , const Animation& anim,float x, float y) {
        // Boucle pour enchainer les images 
        int spriteIndex = anim.startFrame + (frameCounter % anim.totalFrames);

        // Pour getter l'image du sprite Sheet 
        C2D_Image image = C2D_SpriteSheetGetImage(sheet, spriteIndex);

        // Dessin de l'image 
        C2D_DrawImageAt(image, x, y, 0.9f, nullptr, 1.0f, 1.0f);
    }

    void fonctionTsisyAnarana(C2D_SpriteSheet sheet , const Animation& anim , bool isMoved, float x, float y) {
        if (isMoved) {
            updateAnimation(anim);
            drawImageWithAnimation(sheet,anim,x,y);
        } else {
            idleAnimation(sheet,x,y);
        }
    }

    bool gooseIsMooving(const Goose* goo) {
        if (goo->vx >= 0) {
            return true;
        }
        return false;
    }
};