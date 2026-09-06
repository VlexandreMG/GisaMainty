#pragma once 

class Goose {
public:
    float x;
    float y;
    int cooldown = 2;

    void attack() {
        while (cooldown != 0) {
            x += 2.0f;
            cooldown -= 1;
        }

        cooldown = 2;
    }
};