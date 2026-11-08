#include "../include/Animation.hh"
#include "../include/Goose.hpp"
#include <citro2d.h>
#include <3ds.h>

class AnimationManager {
public:
    int frameCounter = 0;
    int tickTimer = 0;
    Goose goose;

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

    void idleAnimation(C2D_SpriteSheet sheet, float x , float y, float angle) {
        resetAnimation();
        C2D_Image image = C2D_SpriteSheetGetImage(sheet, frameCounter);
        
        C2D_DrawParams params = defineParams(x, y, angle);
        C2D_DrawImage(image, &params);
    }

    C2D_DrawParams defineParams(float x , float y , float angle) {
        C2D_DrawParams params;
        memset(&params, 0, sizeof(params));
        params.pos.x = x;
        params.pos.y = y;
        params.angle = angle;       // On applique l'angle ici aussi !
        params.center.x = 0.5f;
        params.center.y = 0.5f;
        params.depth = 0.9f;

        return params;
    }

    void drawImageWithAnimation(C2D_SpriteSheet sheet , const Animation& anim,float x, float y, float angle) {
        // Boucle pour enchainer les images 
        int spriteIndex = anim.startFrame + (frameCounter % anim.totalFrames);

        // Pour getter l'image du sprite Sheet 
        C2D_Image image = C2D_SpriteSheetGetImage(sheet, spriteIndex);

        // Definis les paramètres de l'image 
        C2D_DrawParams params = defineParams(x,y,angle);

        // Dessin de l'image 
        C2D_DrawImage(image,&params);
    }

    void fonctionTsisyAnarana(C2D_SpriteSheet sheet , const Animation& anim , bool isMoved, float x, float y ,float angle) {
        if (isMoved) {
            updateAnimation(anim);
            drawImageWithAnimation(sheet,anim,x,y,angle);
        } else {
            idleAnimation(sheet,x,y,angle);
        }
    }

    bool gooseIsMooving(u32 kheld) {
        return (kheld & KEY_DRIGHT || kheld & KEY_DLEFT);
    }

    bool gooseIsFlying(u32 kheld , Goose& g) {
        if (kheld & KEY_B) {
            if (g.gas != 0) {
                g.isFlying = true;
                return true;
            } else if ((g.gas == 0) && g.isGrounded == true) {
                g.isFlying = false;
                return false;
            }
        }
        return false;
    }
};