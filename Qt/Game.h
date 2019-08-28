//
// Created by YY  WYX on 2019/8/23.
//

#ifndef HELLO_GAME_H
#define HELLO_GAME_H


#include <iostream>
#include <vector>
#include <random>
#include "random.h"

struct Game {
private:
    int currentPlayer = 0;
    std::vector<int> r;
    std::vector<int> randoms;
public:
    Game(int n) {
        for (int i = 0; i < n; ++i) { r.push_back(i); }
    }

    int play(int n) {
        int indexToErase = (currentPlayer + n) % r.size();
        int result = r[indexToErase];
        r.erase(r.begin() + indexToErase);

        return result;
    }

    std::vector<int> playing(int n) {
        std::vector<int> b;
        for (int i = 0; i < n; i++) {
            static YY yy = YY(1, 6, n);
            int diceNum = yy.roll();
            b.push_back(play(diceNum));
            randoms.push_back(diceNum);
        }
        return b;
    }

    std::vector<int> getRandoms() {
        return randoms;
    }
};

#endif //HELLO_GAME_H