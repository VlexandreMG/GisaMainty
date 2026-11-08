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
        
        C2D_DrawParams params = defineParams(image,x, y, angle);
        C2D_DrawImage(image, &params);
    }

    C2D_DrawParams defineParams(C2D_Image image, float x, float y, float angle) {
    C2D_DrawParams params;
    memset(&params, 0, sizeof(params));

    // Taille réelle de l'image (avant, elle restait à 0 → oie invisible)
    params.pos.w = image.subtex->width;
    params.pos.h = image.subtex->height;

    // Centre de rotation en PIXELS : le milieu de l'oie
    params.center.x = params.pos.w / 2.0f;
    params.center.y = params.pos.h / 2.0f;

    // pos = point de rotation → on décale pour que (x, y) reste le coin haut-gauche
    params.pos.x = x + params.center.x;
    params.pos.y = y + params.center.y;

    params.angle = angle;
    params.depth = 0.9f;

    return params;
}


    void drawImageWithAnimation(C2D_SpriteSheet sheet , const Animation& anim,float x, float y, float angle) {
        // Boucle pour enchainer les images 
        int spriteIndex = anim.startFrame + (frameCounter % anim.totalFrames);

        // Pour getter l'image du sprite Sheet 
        C2D_Image image = C2D_SpriteSheetGetImage(sheet, spriteIndex);

        // Definis les paramètres de l'image 
        C2D_DrawParams params = defineParams(image,x,y,angle);

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