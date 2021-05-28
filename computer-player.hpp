#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H


#include <array>
#include "player.hpp"
#include "board.hpp"


class ComputerPlayer : public Player {
    enum class Difficulty { EASY, MEDIUM, HARD };

    private:
        Difficulty difficulty;
        
    public:
        ComputerPlayer(Board &board, std::string difficulty)
            : Player(board), difficulty{ initDifficulty(difficulty) } { }

        std::array<int, 2> chooseMove();
        std::string getStringDifficulty() const;

    private:
        Difficulty initDifficulty(std::string difficulty);
        static bool checkForWin(std::array<char, 3> line, char symbol);
};


#endif // COMPUTER_PLAYER_H