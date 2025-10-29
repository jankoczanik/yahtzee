#ifndef Functions_h
#define Functions_h

#include <string>

#include "Scorecard.h"
#include "Dice.h"

void printDice(const Dice dice[5]);
void playerTurn(Dice dice[5], Scorecard& score);
std::string promptReroll();
int promptCategory(const Scorecard& score);
void reroll(Dice dice[5], std::string token);

#endif