#include <iostream>

#include "../include/Functions.h"

void printDice(const Dice dice[5]) {
    for (int i = 0; i < 4; i ++) {
        std::cout << dice[i].getFace() << " ";
    }
    std::cout << dice[4].getFace();
}

void playerTurn(Dice dice[5], Scorecard& score) {

    std::cout << "Roll #1: ";
    printDice(dice);
    std::cout << std::endl;
    reroll(dice, promptReroll());

    std::cout << std::endl << "Roll #2: ";
    printDice(dice);
    std::cout << std::endl;
    reroll(dice, promptReroll());

    std::cout << std::endl << "Roll #3: ";
    printDice(dice);
    std::cout << std::endl;
    int category = promptCategory(score);
    int scoring = score.score(dice, category, true);

    std::cout << std::endl << "Scored " << scoring << " points for " << score.getCategoryName(category) << "!" << std::endl;

}

std::string promptReroll() {
    std::cout << "Reroll? (eg. ynynn) >> ";
    std::string result;
    std::getline(std::cin, result);
    return result + "nnnnn";
}

int promptCategory(const Scorecard& score) {
    int res;
    do {
        std::cout << "Enter scoring category (#) >> ";
        std::cin >> res;
    } while (!score.available(res, true));
    return res;
}

void reroll(Dice dice[5], std::string token) {
    for (int i = 0; i < 5; i ++)
        if (token[i] == 'y')
            dice[i].roll();
}
