#include <cstdlib>

#include <../include/Dice.h>

Dice::Dice() {
    roll();
}

void Dice::roll() {
    face = rand() % 6 + 1;
}

int Dice::getFace() const {
    return face;
}