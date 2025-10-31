#include <iostream>

#include "../include/Dice.h"
#include "../include/Scorecard.h"
#include "../include/Functions.h"

int main() {

    srand(time(NULL));

    Scorecard score;
    Dice hand[5];

    for (int i = 0; i < 13; i ++) {
        score.printScorecard();
        playerTurn(hand, score);
        botTurn(hand, score);
    }

    score.printScorecard();

    return 0;
}