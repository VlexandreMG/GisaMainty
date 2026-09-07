#pragma once 

class Goose {
public:
    float x;
    float y;
    float w = 15.0f;
    float h = 15.0f;
    int attackFrameLeft = 0;
    int health = 3;
    bool isAttacking = false;

    void attack() {
        if (attackFrameLeft <= 0) {
            attackFrameLeft = 15;
            isAttacking = true;
        }
    }

    bool checkCollision(const Goose& other) const {
        float MonMurGauche = x;
        float MonMurDroit = x+w;
        float MonMurHaut = y;
        float MonMurBas = y+h;

        float OtMurGauche = other.x;
        float OtMurDroit = other.x + other.w;
        float OtMurHaut = other.y;
        float OtMurBas = other.y + other.h;

        bool CollGauche = MonMurDroit > OtMurGauche;
        bool CollDroite = MonMurGauche < OtMurDroit;
        bool CollHaut = MonMurHaut < OtMurBas;
        bool CollBas = MonMurBas > OtMurHaut;

        return CollDroite && CollGauche && CollHaut && CollBas; 
    }

    void update() {
        if (attackFrameLeft > 0) {
            x += 1.0f;
            attackFrameLeft--;
        }
    }
};