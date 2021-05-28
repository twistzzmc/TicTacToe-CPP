#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H


#include <array>
#include "player.hpp"
#include "board.hpp"


class HumanPlayer : public Player {
    public:
        HumanPlayer(Board &board) : Player(board) { }

        std::array<int, 2> chooseMove();
        std::string getStringDifficulty() const { return "human"; }

    private:
        bool validateUserInput(int fieldIndex);
};


#endif // HUMAN_PLAYER_H