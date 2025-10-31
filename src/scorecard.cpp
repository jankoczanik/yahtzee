#include "../include/Scorecard.h"

Scorecard::Scorecard() {
    for (int i = 0; i < 13; i++) {
        player[i] = -1;
        bot[i] = -1;
    }
}

void Scorecard::printScorecard() const {
    std::cout << " Upper Section   | You | Bot       Lower Section   | You | Bot \n";
    std::cout << "-----------------|-----|-----     -----------------|-----|-----\n";
    for (int i = 1; i <= 6; i ++) {
        std::cout << " [" << (i) << "] " << getCategoryName(i) << " | " << formatScore(getScore(i, true)) << " | " << formatScore(getScore(i, false)) << "      ";
        std::cout << " [" << (i + 6) << "] " << getCategoryName(i + 6) << " | " << formatScore(getScore(i + 6, true)) << " | " << formatScore(getScore(i + 6, false)) << "\n";
    }
    std::cout << "-----------------|-----|-----     ";
    std::cout << " [13] Chance     | " << formatScore(getScore(13, true)) << " | " << formatScore(getScore(13, false)) << "\n";
    std::cout << " Subtotal        | " << formatScore(getUpperTotal(true)) << " | " << formatScore(getUpperTotal(false)) << "      ";
    std::cout << " ----------------|-----|-----" << std::endl;
    std::cout << " Bonus           | " << formatScore(getUpperBonus(true)) << " | " << formatScore(getUpperBonus(false)) << "      ";
    std::cout << " Lower Total     | " << formatScore(getLowerTotal(true)) << " | " << formatScore(getLowerTotal(false)) << std::endl;
    std::cout << " Upper Total     | " << formatScore(getUpperTotal(true) + getUpperBonus(true)) << " | " << formatScore(getUpperTotal(false) + getUpperBonus(false))  << "      ";
    std::cout << " GRAND TOTAL     | " << formatScore(getGrandTotal(true)) << " | " << formatScore(getGrandTotal(false)) << std::endl;
}

int Scorecard::getUpperTotal(bool isPlayer) const {
    int total = 0, s;
    for (int i = 1; i <= 6; i++) {
        s = getScore(i, isPlayer);
        if (s != -1) total += s;
    } 
    return total;
}

int Scorecard::getUpperBonus(bool isPlayer) const {
   return (getUpperTotal(isPlayer) >= 63) ? 35 : 0;
}

int Scorecard::getLowerTotal(bool isPlayer) const {
    int total = 0, s;
    for (int i = 7; i <= 13; i++) {
        s = getScore(i, isPlayer);
        if (s != -1) total += s;
    } 
    return total;
}

int Scorecard::getGrandTotal(bool isPlayer) const {
    return getUpperTotal(isPlayer) + getUpperBonus(isPlayer) + getLowerTotal(isPlayer);
}

int Scorecard::getScore(int category, bool isPlayer) const {
    if (isPlayer)
        return player[category - 1];
    else    
        return bot[category - 1];
}

std::string Scorecard::formatScore(int score) const {
    if (score == -1)
        return "   ";
    else if (score < 10)
        return "  " + std::to_string(score);
    else if (score < 100)
        return " " + std::to_string(score);
    else
        return "" + std::to_string(score);
}

std::string Scorecard::getCategoryName(int category) const {
    if (category < 1 || category > 13) return "";
    std::string categories[] = {
        "One's      ",
        "Two's      ",
        "Three's    ",
        "Four's     ",
        "Five's     ",
        "Six's      ",
        "3 of Kind  ",
        "4 of Kind  ",
        "F House    ",
        "S Straight",
        "L Straight",
        "Yahtzee   ",
        "Chance    ",
    };
    return categories[category - 1];
}

int Scorecard::score(const Dice hand[], int category, bool isPlayer) {
    int scoring = calcScore(hand, category);

    if (isPlayer)
        player[category - 1] = scoring;
    else
        bot[category - 1] = scoring;

    return scoring;
}

int Scorecard::calcScore(const Dice hand[], int category) const {
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
        total += freq[hand[i].getFace() - 1];
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

bool Scorecard::available(int category, bool isPlayer) const {
    if (category < 1 || category > 13) return false;
    return isPlayer ? (player[category - 1] == -1) : (bot[category - 1] == -1);
}