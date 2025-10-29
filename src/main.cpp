#include <iostream>

#include "../include/Dice.h"
#include "../include/Scorecard.h"
#include "../include/Functions.h"

int main() {

    srand(time(NULL));

    Scorecard score;
    Dice hand[5];

    playerTurn(hand, score);

    return 0;
}