#ifndef Functions_h
#define Functions_h

#include <string>
#include "Dice.h"

void printDice(const Dice dice[5]);
void playerTurn(Dice dice[5]);
std::string promptReroll();
void reroll(Dice dice[5], std::string token);

#endif