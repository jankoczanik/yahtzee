#include <iostream>

#include "../include/Functions.h"

void printDice(const Dice dice[5]) {
    for (int i = 0; i < 4; i ++) {
        std::cout << dice[i].getFace() << " ";
    }
    std::cout << dice[4].getFace();
}

void playerTurn(Dice dice[5]) {

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

}

std::string promptReroll() {
    std::cout << "Reroll? (eg. ynynn) >> ";
    std::string result;
    std::getline(std::cin, result);
    return result + "nnnnn";
}

void reroll(Dice dice[5], std::string token) {
    for (int i = 0; i < 5; i ++)
        if (token[i] == 'y')
            dice[i].roll();
}
