#pragma once 

class Goose {
public:
    Vector2 position;

    void attack() {
        position.x += 2.0f;
    }
}