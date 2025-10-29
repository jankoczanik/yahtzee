#ifndef Scorecard_h
#define Scorecard_h

#include "Dice.h"

class Scorecard {
    public:
        Scorecard();
        void printScorecard() const;
        int score(int, Dice[]);

    private:
        int player[13];
        int bot[13];

};

#endif