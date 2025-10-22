#include <iostream>

class Score {

    public:
    
    int OnesScore(int *dice) {
        int total = 0;
        for (int i = 0; i < 5; i ++) {
            if (dice[i] == 1) total += 1;
        } 
        return total;
    }

    int TwosScore(int *dice) {
        int total = 0;
        for (int i = 0; i < 5; i ++) {
            if (dice[i] == 2) total += 2;
        } 
        return total;
    }

    int ThreesScore(int *dice) {
        int total = 0;
        for (int i = 0; i < 5; i ++) {
            if (dice[i] == 3) total += 3;
        } 
        return total;
    }

    int FoursScore(int *dice) {
        int total = 0;
        for (int i = 0; i < 5; i ++) {
            if (dice[i] == 4) total += 4;
        } 
        return total;
    }

    int FivesScore(int *dice) {
        int total = 0;
        for (int i = 0; i < 5; i ++) {
            if (dice[i] == 5) total += 5;
        } 
        return total;
    }

    int SixesScore(int *dice) {
        int total = 0;
        for (int i = 0; i < 5; i ++) {
            if (dice[i] == 6) total += 6;
        } 
        return total;
    }

    int ThreeKindScore(int *dice) {
        int frequency[] = {0, 0, 0, 0, 0, 0};
        int total = 0;
        for (int i = 0; i < 5; i ++) {
            frequency[dice[i] - 1] ++;
            total += dice[i];
        }
        for (int i = 0; i < 6; i ++) {
            if (frequency[i] > 2)
                return total;
        }
        return 0;
    }

    int FourKindScore(int *dice) {
        int frequency[] = {0, 0, 0, 0, 0, 0};
        int total = 0;
        for (int i = 0; i < 5; i ++) {
            frequency[dice[i] - 1] ++;
            total += dice[i];
        }
        for (int i = 0; i < 6; i ++)
            if (frequency[i] > 3)
                return total;
        return 0;
    }

    int FullHouseScore(int *dice) {
        int frequency[] = {0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 5; i ++)
            frequency[dice[i] - 1] ++;
        bool pair = false;
        bool triplet = false;
        for (int i = 0; i < 6; i ++) {
            if (frequency[i] == 2) pair = true;
            if (frequency[i] == 3) triplet = true;
            if (pair && triplet) return 25;
        }
        return 0;
    }

    int SmallStraightScore(int *dice) {
        int frequency[] = {0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 5; i ++)
            frequency[dice[i] - 1] ++;
        int count = 0;
        for (int i = 0; i < 6; i ++) {
            if (frequency[i] > 0) count ++;
            else count = 0;
            if (count > 3) return 30;
        }
        return 0;
    }

    int LargeStraightScore(int *dice) {
        int frequency[] = {0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 5; i ++)
            frequency[dice[i] - 1] ++;
        int count = 0;
        for (int i = 0; i < 6; i ++) {
            if (frequency[i] > 0) count ++;
            else count = 0;
            if (count > 4) return 40;
        }
        return 0;
    }

    int YahtzeeScore(int *dice) {
        return 
            dice[0] == dice[1] &&
            dice[1] == dice[2] &&
            dice[2] == dice[3] &&
            dice[3] == dice[4] ? 50 : 0;
    }

    int ChanceScore(int *dice) {
        int total = 0;
        for (int i = 0; i < 5; i ++) {
            total += dice[i];
        }
        return total;    
    }
};

void printScorecard(int *playerScorecard, int *botScorecard);
std::string formatScore(int number);
int getTotal(int *score, int start, int end);
int upperBonus(int *score);
void playerTurn(int *playerScorecard);
void botTurn(int *botScorecard);
void printDice(int *dice);
void promptDice(int *dice);
void scoreTurn(int *dice, int *scorecard, int res);
bool validCategory(int *score, int num);
int roll();

int main() {

    int playerScorecard[13];
    int botScorecard[13];
    for (int i = 0; i < 13; i ++) {
        playerScorecard[i] = -1;
        botScorecard[i] = -1;
    }

    srand(time(NULL));

    for (int i = 0; i < 13; i ++) {
        printScorecard(playerScorecard, botScorecard);
        playerTurn(playerScorecard);
        botTurn(botScorecard);
    }
    printScorecard(playerScorecard, botScorecard);
}

void botTurn(int *botScorecard) {
    std::cout << "\nBot's Turn!\n";
    int dice[5];
    int frequency[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i ++) {
        dice[i] = roll();
        frequency[dice[i] - 1] ++;
    }
    std::cout << "Roll #1: ";
    printDice(dice);
    int max = 0;
    int maxNum = 0;
    for (int i = 0; i < 6; i ++) {
        if (frequency[i] >= max && botScorecard[i] < 0) {
            max = frequency[i];
            maxNum = i + 1;
        }
    }
    for (int i = 0; i < 5; i ++) {
        if (dice[i] != maxNum) {
            frequency[dice[i] - 1] --;
            dice[i] = roll();
            frequency[dice[i] - 1] ++;
        }
    }
    std::cout << "Roll #2: ";
    printDice(dice);
    max = 0;
    maxNum = 0;
    for (int i = 0; i < 6; i ++) {
        if (frequency[i] >= max && botScorecard[i] < 0) {
            max = frequency[i];
            maxNum = i + 1;
        }
    }
    for (int i = 0; i < 5; i ++) {
        if (dice[i] != maxNum) {
            frequency[dice[i] - 1] --;
            dice[i] = roll();
            frequency[dice[i] - 1] ++;
        }
    }
    std::cout << "Roll #3: ";
    printDice(dice);
    max = 0;
    maxNum = 0;
    for (int i = 0; i < 6; i ++) {
        if (frequency[i] >= max) {
            max = frequency[i];
            maxNum = i;
        }
    }
    Score score;
    bool joker = (score.YahtzeeScore(dice) == 50 && botScorecard[11] > 0);
    if (joker) {
        for (int i = 0; i < 6; i ++) {
            if (botScorecard[i] < 0) {
                botScorecard[i] += 50;
                std::cout << "Scoring Category: " << i + 1;
                return;
            }
        }
        for (int i = 10; i >= 6; i --) {
            if (botScorecard[i] < 0) {
                botScorecard[i] += 50;
                std::cout << "Scoring Category: " << i + 1;
                return;
            }
        }
        if (botScorecard[12] < 0) {
            botScorecard[12] += 50;
            std::cout << "Scoring Category: 13";
            return;
        }
    } else {
        if (score.YahtzeeScore(dice) > 0 && botScorecard[11] < 0) {
            botScorecard[11] = score.YahtzeeScore(dice);
            std::cout << "Scoring Category: 12";
            return;
        } else if (score.LargeStraightScore(dice) > 0 && botScorecard[10] < 0) {
            botScorecard[10] = score.LargeStraightScore(dice);
            std::cout << "Scoring Category: 11";
            return;
        } else if (score.FourKindScore(dice) > 0 && botScorecard[7] < 0) {
            botScorecard[7] = score.FourKindScore(dice);
            std::cout << "Scoring Category: 8";
            return;
        } else if (score.SmallStraightScore(dice) > 0 && botScorecard[9] < 0) {
            botScorecard[9] = score.SmallStraightScore(dice);
            std::cout << "Scoring Category: 10";
            return;
        } 
        int threshold = 3;
        if (score.SixesScore(dice) >= threshold * 6 && botScorecard[5] < 0) {
            botScorecard[5] = score.SixesScore(dice);
            std::cout << "Scoring Category: 6";
            return;
        } else if (score.FivesScore(dice) >= threshold * 5 && botScorecard[4] < 0) {
            botScorecard[4] = score.FivesScore(dice);
            std::cout << "Scoring Category: 5";
            return;
        } else if (score.FoursScore(dice) >= threshold * 4 && botScorecard[3] < 0) {
            botScorecard[3] = score.FoursScore(dice);
            std::cout << "Scoring Category: 4";
            return;
        } else if (score.ThreesScore(dice) >= threshold * 3 && botScorecard[2] < 0) {
            botScorecard[2] = score.ThreesScore(dice);
            std::cout << "Scoring Category: 3";
            return;
        } else if (score.TwosScore(dice) >= threshold * 2 && botScorecard[1] < 0) {
            botScorecard[1] = score.TwosScore(dice);
            std::cout << "Scoring Category: 2";
            return;
        } else if (score.OnesScore(dice) >= threshold && botScorecard[0] < 0) {
            botScorecard[0] = score.OnesScore(dice);
            std::cout << "Scoring Category: 1";
            return;
        }
        if (score.FullHouseScore(dice) > 0 && botScorecard[8] < 0) {
            botScorecard[8] = score.FullHouseScore(dice);
            std::cout << "Scoring Category: 9";
            return;
        } else if (score.ThreeKindScore(dice) > 0 && botScorecard[6] < 0) {
            botScorecard[6] = score.ThreeKindScore(dice);
            std::cout << "Scoring Category: 7";
            return;
        }
        if (botScorecard[12] < 0) {
            botScorecard[12] = score.ChanceScore(dice);
            std::cout << "Scoring Category: 13";
            return;
        }
        for (int threshold = 2; threshold > 0; threshold --) {
            if (score.OnesScore(dice) >= threshold && botScorecard[0] < 0) {
                botScorecard[0] = score.OnesScore(dice);
                std::cout << "Scoring Category: 1";
                return;
            } else if (score.TwosScore(dice) >= threshold * 2 && botScorecard[1] < 0) {
                botScorecard[1] = score.TwosScore(dice);
                std::cout << "Scoring Category: 2";
                return;
            } else if (score.ThreesScore(dice) >= threshold * 3 && botScorecard[2] < 0) {
                botScorecard[2] = score.ThreesScore(dice);
                std::cout << "Scoring Category: 3";
                return;
            } else if (score.FoursScore(dice) >= threshold * 4 && botScorecard[3] < 0) {
                botScorecard[3] = score.FoursScore(dice);
                std::cout << "Scoring Category: 4";
                return;
            } else if (score.FivesScore(dice) >= threshold * 5 && botScorecard[4] < 0) {
                botScorecard[4] = score.FivesScore(dice);
                std::cout << "Scoring Category: 5";
                return;
            } else if (score.SixesScore(dice) >= threshold * 6 && botScorecard[5] < 0) {
                botScorecard[5] = score.SixesScore(dice);
                std::cout << "Scoring Category: 6";
                return;
            }
        }
        if (botScorecard[11] < 0) {
            botScorecard[11] = 0;
            std::cout << "Scoring Category: 12";
            return;
        }
        if (botScorecard[10] < 0) {
            botScorecard[10] = 0;
            std::cout << "Scoring Category: 11";
            return;
        }
        if (botScorecard[7] < 0) {
            botScorecard[7] = 0;
            std::cout << "Scoring Category: 8";
            return;
        }
        if (botScorecard[9] < 0) {
            botScorecard[9] = 0;
            std::cout << "Scoring Category: 10";
            return;
        }
        if (botScorecard[8] < 0) {
            botScorecard[8] = 0;
            std::cout << "Scoring Category: 9";
            return;
        }
        if (botScorecard[6] < 0) {
            botScorecard[6] = 0;
            std::cout << "Scoring Category: 7";
            return;
        }
        for (int i = 0; i < 6; i ++) {
            if (botScorecard[i] < 0) {
                botScorecard[i] = 0;
                std::cout << "Scoring Category: " << i + 1;
                return;
            }
        }
        
    }
}

void playerTurn(int *playerScorecard) {
    std::cout << "Your Turn!\n";
    int dice[5];
    for (int i = 0; i < 5; i ++) {
        dice[i] = roll();
    }
    promptDice(dice);

    int res;
    do {
        std::cout << "Enter scoring category (#) >> ";
        std::cin >> res;
    } while (!validCategory(playerScorecard, res));
    scoreTurn(dice, playerScorecard, res);
}

void scoreTurn(int *dice, int *scorecard, int res) {
    Score score;
    res --;

    bool joker = (score.YahtzeeScore(dice) == 50 && scorecard[11] > 0);
    switch (res) {
        case 0: scorecard[res] = joker ? 50 : score.OnesScore(dice);
                break;
        case 1: scorecard[res] = joker ? 50 : score.TwosScore(dice);
                break;
        case 2: scorecard[res] = joker ? 50 : score.ThreesScore(dice);
                break;
        case 3: scorecard[res] = joker ? 50 : score.FoursScore(dice);
                break;
        case 4: scorecard[res] = joker ? 50 : score.FivesScore(dice);
                break;
        case 5: scorecard[res] = joker ? 50 : score.SixesScore(dice);
                break;
        case 6: scorecard[res] = joker ? 50 : score.ThreeKindScore(dice);
                break;
        case 7: scorecard[res] = joker ? 50 : score.FourKindScore(dice);
                break;
        case 8: scorecard[res] = joker ? 50 : score.YahtzeeScore(dice);
                break;
        case 9: scorecard[res] = joker ? 50 : score.SmallStraightScore(dice);
                break;
        case 10: scorecard[res] = joker ? 50 : score.LargeStraightScore(dice);
                break;
        case 11: scorecard[res] = joker ? 50 : score.YahtzeeScore(dice);
                break;
        case 12: scorecard[res] = joker ? 50 : score.ChanceScore(dice);
                break;
    }
}

bool validCategory(int *score, int num) {
    if (num < 1 || num > 13)
        return false;
    return score[num - 1] == -1;
}

void promptDice(int *dice) {
    std::cout << "Roll #1: ";
    std::string result;
    printDice(dice);
    do {
        std::cout << "Reroll? (eg. ynynn) >> ";
        std::cin >> result;
    } while (result.size() < 5);
    for (int i = 0; i < 5; i ++) {
        if (result[i] == 'y' || result[i] == 'Y') {
            dice[i] = roll();
        }
    }
    std::cout << "Roll #2: ";
    printDice(dice);
    std::cout << "Reroll? (eg. ynynn) >> ";
    std::cin >> result;
    for (int i = 0; i < 5; i ++) {
        if (result[i] == 'y' || result[i] == 'Y') {
            dice[i] = roll();
        }
    }
    std::cout << "Roll #3: ";
    printDice(dice);
}

void printDice(int *dice) {
    for (int i = 0; i < 5; i ++) {
        std::cout << dice[i] << " ";
    }
    std::cout << '\n';
}

int roll() {
    return rand() % 6 + 1;
}

void printScorecard(int *playerScorecard, int *botScorecard) {
    std::cout << "\n\n******* UPPER  SECTION *******        ******* LOWER  SECTION *******" << '\n';
    std::cout << " Section      |  You  |  Bot           Section      |  You  |  Bot  " << '\n';
    std::cout << "--------------|-------|-------        --------------|-------|-------" << '\n';
    std::cout << " [1] Ones     |  " << formatScore(playerScorecard[0]) << 
                              " |  " << formatScore(botScorecard[0]) << "         ";
    std::cout << " [7] 3 Kind   |  " << formatScore(playerScorecard[6]) << 
                              " |  " << formatScore(botScorecard[6]) << " \n";
    std::cout << " [2] Twos     |  " << formatScore(playerScorecard[1]) << 
                              " |  " << formatScore(botScorecard[1]) << "         ";   
    std::cout << " [8] 4 Kind   |  " << formatScore(playerScorecard[7]) << 
                              " |  " << formatScore(botScorecard[7]) << " \n";                                    
    std::cout << " [3] Threes   |  " << formatScore(playerScorecard[2]) << 
                              " |  " << formatScore(botScorecard[2]) << "         ";
    std::cout << " [9] F. House |  " << formatScore(playerScorecard[8]) << 
                              " |  " << formatScore(botScorecard[8]) << " \n";
    std::cout << " [4] Fours    |  " << formatScore(playerScorecard[3]) << 
                              " |  " << formatScore(botScorecard[3]) << "         ";
    std::cout << " [10] Sm Strt |  " << formatScore(playerScorecard[9]) << 
                              " |  " << formatScore(botScorecard[9]) << " \n"; 
    std::cout << " [5] Fives    |  " << formatScore(playerScorecard[4]) << 
                              " |  " << formatScore(botScorecard[4]) << "         "; 
    std::cout << " [11] Lg Strt |  " << formatScore(playerScorecard[10]) << 
                              " |  " << formatScore(botScorecard[10]) << " \n";           
    std::cout << " [6] Sixes    |  " << formatScore(playerScorecard[5]) << 
                              " |  " << formatScore(botScorecard[5]) << "         ";
    std::cout << " [12] Yahtzee |  " << formatScore(playerScorecard[11]) << 
                              " |  " << formatScore(botScorecard[11]) << " \n";
    std::cout << "--------------|-------|-------        ";
    std::cout << " [13] Chance  |  " << formatScore(playerScorecard[12]) << 
                              " |  " << formatScore(botScorecard[12]) << " \n";
    std::cout << " Subtotal     |  " << formatScore(getTotal(playerScorecard, 0, 5)) <<
                              " |  " << formatScore(getTotal(botScorecard, 0, 5)) << "         ";
    std::cout << "--------------|-------|-------\n";                  
    std::cout << " Bonus        |  " << formatScore(upperBonus(playerScorecard)) <<
                              " |  " << formatScore(upperBonus(botScorecard)) << "         ";
    std::cout << " Subtotal     |  " << formatScore(getTotal(playerScorecard, 6, 12)) <<
                              " |  " << formatScore(getTotal(botScorecard, 6, 12)) << " \n";
    std::cout << " Total        |  " << formatScore(getTotal(playerScorecard, 0, 5) + upperBonus(playerScorecard)) <<
                              " |  " << formatScore(getTotal(botScorecard, 0, 5) + upperBonus(botScorecard)) << "         ";
    std::cout << " Grand Total  |  " << formatScore(getTotal(playerScorecard, 0, 12) + upperBonus(playerScorecard)) <<
                              " |  " << formatScore(getTotal(botScorecard, 0, 12) + upperBonus(botScorecard)) << " \n";
    std::cout << "******************************        ******************************\n\n";
}

int upperBonus(int *score) {
    if (getTotal(score, 0, 5) >= 63) {
        return 35;
    } else {
        return 0;
    }
}

int getTotal(int *score, int start, int end) {
    int total = 0;
    for (int i = start; i <= end; i ++) {
        if (score[i] > 0) total += score[i];
    }
    return total;
}

std::string formatScore(int number) {
    if (number == -1) {
        return "    ";
    } else if (number < 10) {
        return "   " + std::to_string(number);
    } else if (number < 100) {
        return "  " + std::to_string(number);
    } else if (number < 1000) {
        return " " + std::to_string(number);
    } else {
        return "" + std::to_string(number);
    }
}