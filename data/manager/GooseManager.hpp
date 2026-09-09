#pragma once 
#include <vector>
#include "../include/Goose.hpp"

class GooseManager {
public:
    std::vector<Goose*> geese;

    Goose* spawnGoose(float X, float Y) {
       Goose* newGoose = new Goose();
       newGoose->x = X;
       newGoose->y = Y;

       geese.push_back(newGoose);
       return newGoose;
    }

    void updateAll() {
        for (Goose* goose : geese) {
            goose.update();
        }
    }

    void clear() {
        for (Goose* goose : geese) {
            delete goose;
        }
        geese.clear();
    }
}