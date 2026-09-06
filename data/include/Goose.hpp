#pragma once 

class Goose {
public:
    float x;
    float y;
    int attackFrameLeft = 0;
    int health = 3;

    void attack() {
        if (attackFrameLeft <= 0) {
            attackFrameLeft = 15;
        }
    }

    void update() {
        if (attackFrameLeft > 0) {
            x += 6.0f;
            attackFrameLeft--;
        }
    }
};