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

    std::cout << "\n\n";

    int player = score.getGrandTotal(true);
    int bot = score.getGrandTotal(false);
    
    if (player > bot) {
        std::cout << "You won! (" << player << '-' << bot << ")";
    } else if (bot > player) {
        std::cout << "Bot won! (" << bot << '-' << player << ")";
    } else {
        std::cout << "It's a draw!";
    }

    return 0;
}