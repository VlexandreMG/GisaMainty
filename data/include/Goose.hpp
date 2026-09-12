#pragma once 

class Goose {
public:
    float x;
    float y;
    float w = 15.0f;
    float h = 15.0f;
    float vy = 2.0f;
    float flyForce = 3.0f;
    float rightForce = 1.0f;
    float leftForce = 1.0f;
    float gas = 2.0f;
    float maxGas = 2.0f;
    float angle = 0.0f;
    int hitFrameLeft = 0;
    int attackFrameLeft = 0;
    int health = 3;
    bool isAttacking = false;
    bool hasHitTarget = false;
    bool isGrounded = false;

    void takeHit(float direction) {
        health--;
        angle = 0.35f * direction;
        hitFrameLeft = 10;
    }

    void mooveRight() {
        x += rightForce;
    }

    void mooveLeft() {
        x -= rightForce;
    }

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
            float direction = (x < target.x) ? 1.0f : 1.0f;
            target.takeHit(direction;)
            if (target.health < 0) target.health = 0;
            hasHitTarget = true;
        }
    }

    void update() {
        if (attackFrameLeft > 0) {
            x += 1.0f;
            attackFrameLeft--;
        } else {
            isAttacking = false;
        }

        if (hitFrameLeft > 0) {
            hitFrameLeft--;
            if (hitFrameLeft == 0) {
                angle = 0;
            }
        }
    }

    void rightBound() {
        if ((x+w) >= 399.0f) {
            x = 399.0f - w;
        }
    }

    void leftBound() {
        if ((x) <= 0.0f) {
            x = 0;
        }
    }

    void upBound() {
        if ((y) <= 0.0f) {
            y = 0;
        }
    }
};