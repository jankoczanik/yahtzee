#ifndef Scorecard_h
#define Scorecard_h

#include <string>

#include "Dice.h"

class Scorecard {
    public:
        Scorecard();
        void printScorecard() const;
        int score(const Dice dice[], int category, bool isPlayer);
        bool available(int category, bool isPlayer) const;
        std::string getCategoryName(int category) const;

    private:
        int getScore(const Dice dice[], int category) const;
        int frequencies(const Dice dice[], int freq[6]) const;
        bool hasKind(const int freq[6], int kind) const;
        bool hasStraight(const int freq[6], int straight) const;
        int player[13];
        int bot[13];

};

#endif