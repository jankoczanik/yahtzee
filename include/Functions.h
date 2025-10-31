#ifndef Functions_h
#define Functions_h

#include <string>

#include "Scorecard.h"
#include "Dice.h"

void printDice(const Dice dice[5]);
void playerTurn(Dice dice[5], Scorecard& score);
void botTurn(Dice dice[5], Scorecard& score);
std::string promptReroll();
std::string botsMove(const Dice dice[5], Scorecard& score);
int promptCategory(const Scorecard& score);
int botsCategory(const Dice dice[5], const Scorecard& score);
void reroll(Dice dice[5], std::string token);

#endif