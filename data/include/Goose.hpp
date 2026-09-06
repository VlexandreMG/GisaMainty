#pragma once 

class Goose {
public:
    float x;
    float y;
    int attackFrameLeft = 0;

    void attack() {
        if (attackFrameLeft <= 0) {
            attackFrameLeft = 2;
        }
    }

    void update() {
        if (attackFrameLeft > 0) {
            x += 2.0f;
            attackFrameLeft--;
        }
    }
};