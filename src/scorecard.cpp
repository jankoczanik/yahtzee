#include "../include/Scorecard.h"

Scorecard::Scorecard() {
    for (int i = 0; i < 13; i++) {
        player[i] = -1;
        bot[i] = -1;
    }
}

void Scorecard::printScorecard() const {

}

int Scorecard::score(const Dice hand[], int category) const {
    if (category <= 6) { // 1's, 2's, 3's, 4's, 5's, 6's

        int total = 0;
        for (int i = 0; i < 5; i ++)
            if (hand[i].getFace() == category)
                total += category;
        return total;

    } else if (category == 7) { // 3 of a kind

        int freq[6];
        int total = frequencies(hand, freq);
        return (hasKind(freq, 3) || hasKind(freq, 4) || hasKind(freq, 5)) ? total : 0;

    } else if (category == 8) { // 4 of a kind

        int freq[6];
        int total = frequencies(hand, freq);
        return (hasKind(freq, 4) || hasKind(freq, 5)) ? total : 0;

    } else if (category == 9) { // full house

        int freq[6];
        frequencies(hand, freq);
        return (hasKind(freq, 3) && hasKind(freq, 2)) ? 25 : 0;

    } else if (category == 10) { // small straight

        int freq[6];
        frequencies(hand, freq);
        return hasStraight(freq, 4) ? 30 : 0;

    } else if (category == 11) { // large straight

        int freq[6];
        frequencies(hand, freq);
        return hasStraight(freq, 5) ? 40 : 0;

    } else if (category == 12) { // yahtzee

        int freq[6];
        frequencies(hand, freq);
        return hasKind(freq, 5) ? 50 : 0;

    } else if (category == 13) { // chance

        int freq[6];
        int total = frequencies(hand, freq);
        return total;

    }

    return 0;

}

int Scorecard::frequencies(const Dice hand[], int freq[6]) const {

    int total = 0;
    for (int i = 0; i < 6; i ++) freq[i] = 0;
    for (int i = 0; i < 5; i ++) {
        freq[hand[i].getFace() - 1] ++;
        total += freq[hand[i].getFace()];
    }
    return total;

}

bool Scorecard::hasKind(const int freq[6], int kind) const {
    for (int i = 0; i < 6; i ++)
        if (freq[i] == kind)
            return true;
    return false;
}

bool Scorecard::hasStraight(const int freq[6], int straight) const {
    int count = 0;
    for (int i = 0; i < 6; i ++) {
        if (freq[i] > 0)
            count ++;
        else   
            count = 0;

        if (count >= straight)
            return true;
    }
    return false;
}