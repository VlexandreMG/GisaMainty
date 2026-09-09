#pragma once 

class Goose {
public:
    float x;
    float y;
    float w = 15.0f;
    float h = 15.0f;
    float vy = 2.0f;
    float flyForce = 10.0f;
    float gas = 1000.0f;
    float maxGas = 1000.0f;
    int attackFrameLeft = 0;
    int health = 3;
    bool isAttacking = false;
    bool hasHitTarget = false;
    bool isGrounded = false;

    void fly() {
        if (gas > 0) {
            vy -= flyForce;
            gas -= 0.2f;
            isGrounded = false;
        }
    }

    void reload() {
        if (isGrounded) {
            gas = maxGas;
        }
    }

    void attack() {
        if (attackFrameLeft <= 0) {
            attackFrameLeft = 15;
            isAttacking = true;
            hasHitTarget = false;
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

    void tryAttack(Goose& target) {
        if (isAttacking && !hasHitTarget && checkCollision(target)) {
            target.health--;
            if (target.health < 0) target.health = 0;
            hasHitTarget = true;
        }
    }

    void update() {
        if (attackFrameLeft > 0) {
            x += 1.0f;
            y += vy;
            attackFrameLeft--;
        } else {
            isAttacking = false;
        }
    }
};