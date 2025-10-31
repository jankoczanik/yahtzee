#include <iostream>

#include "../include/Functions.h"
#include "../include/Scorecard.h"

void printDice(const Dice dice[5]) {
    for (int i = 0; i < 4; i ++) {
        std::cout << dice[i].getFace() << " ";
    }
    std::cout << dice[4].getFace();
}

void botTurn(Dice dice[5], Scorecard& score) {

    std::cout << std::endl << "BOT'S TURN: " << std::endl << std::endl;

    reroll(dice, "yyyyy");
    std::cout << "Roll #1: ";
    printDice(dice);

    reroll(dice, botsMove(dice, score));
    std::cout << std::endl << "Roll #2: ";
    printDice(dice);

    reroll(dice, botsMove(dice, score));
    std::cout << std::endl << "Roll #3: ";
    printDice(dice);

    int category = botsCategory(dice, score);
    int scoring = score.score(dice, category, false);

    std::cout << std::endl << "Bot scored " << scoring << " points : " << score.getCategoryName(category) << std::endl << std::endl;

}

void playerTurn(Dice dice[5], Scorecard& score) {

    std::cout << std::endl << "YOUR TURN: " << std::endl << std::endl;

    reroll(dice, "yyyyy");
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

    std::cout << std::endl << "You scored " << scoring << " points : " << score.getCategoryName(category) << std::endl << std::endl;

}

std::string promptReroll() {
    std::cout << "Reroll? (eg. ynynn) >> ";
    std::string result;
    std::getline(std::cin, result);
    return result + "nnnnn";
}

int botsCategory(const Dice dice[5], const Scorecard& score) {
    int freq[6];
    score.frequencies(dice, freq);

    // LOWER CATEGORIES:

    // Prioritize Yahtzee, Straights, Full House:
    for (int i = 12; i >= 9; i --) {
        if (score.calcScore(dice, i) > 0 && score.available(i, false)) {
            return i;
        }
    }
    // Take 4 of a Kind if Strong:
    if (score.calcScore(dice, 8) > 15 && score.available(8, false)) return 8;
    // Take 3 of a Kind if Strong:
    if (score.calcScore(dice, 7) > 18 && score.available(7, false)) return 7;
    
    // UPPER CATEGORIES:

    // Take Upper if 3+
    for (int i = 6; i >= 1; i --) {
        if (score.calcScore(dice, i) >= i * 3 && score.available(i, false)) {
            return i;
        }
    }

    // FALLBACK:

    // Take Chance:
    if (score.available(13, false)) return 13;
    // Take Upper if 2+
    for (int i = 6; i >= 1; i --) {
        if (score.calcScore(dice, i) >= i * 2 && score.available(i, false)) {
            return i;
        }
    }
    // Take Lowest Upper if can get Upper Bonus:
    for (int i = 1; i <= 6; i ++) {
        if (score.calcScore(dice, i) + score.getUpperTotal(false) >= 63 && score.available(i, false))
            return i;
    }
    // Sacrifice Lowest Category:
    for (int i = 9; i <= 12; i ++) {
        if (score.available(i, false)) return i;
    }
    // Sacrifice the Kinds:
    if (score.available(8, false)) return 8;
    if (score.available(7, false)) return 7;
    // Sacrifice the Uppers:
    for (int i = 1; i <= 6; i ++) {
        if (score.available(i, false)) return i;
    }

    return 0;
}

std::string botsMove(const Dice dice[5], Scorecard& score) {

    int freq[6];
    score.frequencies(dice, freq);

    if (score.hasKind(freq, 5)) {
        // Has a yahtzee, don't reroll
        return "nnnnn";
    }
    if (score.hasKind(freq, 3) && score.hasKind(freq, 2)) {
        // Has a full house, don't reroll
        return "nnnnn";
    }
    if (score.hasKind(freq, 4) || score.hasKind(freq, 3)) {
        // Has a 3/4 of a kind, reroll odd one(s) out
        int rollingFor;
        std::string rerolling = "";

        for (int i = 0; i < 6; i ++) if (freq[i] > 2) rollingFor = i + 1;
        for (int i = 0; i < 5; i ++) rerolling += (dice[i].getFace() == rollingFor) ? 'n' : 'y';

        return rerolling;
    }
    if (score.hasStraight(freq, 5) && score.available(11, false)) {
        // Has a large straight, don't reroll
        return "nnnnn";
    }
    if (score.hasStraight(freq, 4) && (score.available(10, false) || score.available(11, false))) {
        // Has a small straight, try for large straight
        bool keep[6] = {false};  // keep[x] = true means keep value (x+1)

        // Determine which small straight exists and mark those values to keep
        if (freq[0] && freq[1] && freq[2] && freq[3]) {         // 1-2-3-4
            keep[0] = keep[1] = keep[2] = keep[3] = true;
        } 
        else if (freq[1] && freq[2] && freq[3] && freq[4]) {    // 2-3-4-5
            keep[1] = keep[2] = keep[3] = keep[4] = true;
        } 
        else if (freq[2] && freq[3] && freq[4] && freq[5]) {    // 3-4-5-6
            keep[2] = keep[3] = keep[4] = keep[5] = true;
        }

        std::string rerolling = "";
        for (int i = 0; i < 5; i++) {
            int face = dice[i].getFace(); // 1–6
            rerolling += keep[face - 1] ? 'n' : 'y';
        }
        return rerolling;
    }
    if (score.hasKind(freq, 2)) {
        // Has a pair, reroll for full house OR 3+ of a kind
        int numPairs = 0;
        int rollingFor;
        int oddOne;
        std::string rerolling = "";
        for (int i = 0; i < 6; i ++) {
            if (freq[i] == 1) oddOne = i + 1;
            if (freq[i] == 2) {
                numPairs ++;
                rollingFor = i + 1;
            }
        }
        if (numPairs == 2) {
            // Go for full house
            for (int i = 0; i < 5; i ++) {
                rerolling += (dice[i].getFace() == oddOne) ? 'y' : 'n';
            }
            return rerolling;
        } else {
            for (int i = 0; i < 5; i ++) {
                rerolling += (dice[i].getFace() == rollingFor) ? 'n' : 'y';
            }
            return rerolling;
        }
    }
    // Has nothing, keep 6's
    std::string rerolling = "";
    for (int i = 0; i < 5; i ++) rerolling += (dice[i].getFace() == 6) ? 'n' : 'y';
    return rerolling;
}

int promptCategory(const Scorecard& score) {
    int res;
    do {
        std::cout << "Enter scoring category (#) >> ";
        std::cin >> res;
    } while (!score.available(res, true));

    std::string dummy;
    std::getline(std::cin, dummy);
    return res;
}

void reroll(Dice dice[5], std::string token) {
    for (int i = 0; i < 5; i ++)
        if (token[i] == 'y')
            dice[i].roll();
}
