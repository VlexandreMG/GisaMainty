#pragma once 
#include <vector>
#include "../include/Goose.hpp"

class System {
public:
    float GRAVITY = 0.3f;
    float GROUNDED_Y = 200.0f;

    void applyPhysics(std::vector<Goose*> geese) {
        for (Goose* goose : geese) {
            if (goose->isGrounded && goose->vy > 0) {
                goose->vy = 0;
            }

            goose->vy += GRAVITY;

            goose->y += goose->vy;

            if ((goose->y + goose->h) > GROUNDED_Y) {
                goose->y = GROUNDED_Y - goose->h;
                goose->vy = 0;
                goose->isGrounded = true;
            } else {
                goose->isGrounded = false;
            }
        }
    }
};