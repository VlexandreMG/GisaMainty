#include "../include/Animation.hh"

class AnimationManager {
public:
    int frameCounter = 0;
    int tickTimer = 0;

    AnimationManager();

    void updateAnimation(const Animation& anim) {
        tickTimer++;

        if (tickTimer >= anim.tickIncrementer) {
            frameCounter++;
            tickTimer = 0;
        }
    }
};