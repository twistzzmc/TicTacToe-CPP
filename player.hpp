#ifndef PLAYER_H
#define PLAYER_H


#include <array>
#include "board.hpp"


class Player {
    protected:
        Board &board;
        char crossOrCircle;

    public:
        Player(Board &board) : board{ board }, crossOrCircle{ ' ' } {}
        ~Player() { }

        char getCrossOrCircle() const { return crossOrCircle; }
        void setCrossOrCircle(char sign) { if (crossOrCircle == ' ') crossOrCircle = sign; }
};


#endif // PLAYER_H