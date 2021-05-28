#ifndef GAME_H
#define GAME_H


#include <array>
#include <type_traits>
#include "board.hpp"


template <class P1, class P2>
class Game {
    static_assert(std::is_base_of<Player, P1>::value, "P1 must be a descendant of Player");
    static_assert(std::is_base_of<Player, P2>::value, "P2 must be a descendant of Player");

    private:
        Board &board;
        P1 firstPlayer;
        P2 secondPlayer;
        int playerTurn;

    public:
        Game(Board &board, P1 firstPlayer, P2 secondPlayer, std::string whoStarts);

        Game(const Game& temp_obj) = delete;
        Game& operator=(const Game& temp_obj) = delete;
        
        int play();

        Board getBoard() const { return board; }
        P1 getFirstPlayer() const { return firstPlayer; }
        P2 getSecondPlayer() const { return secondPlayer; }
        int getPlayerTurn() const { return playerTurn; }

    private:
        int initWhoStarts(std::string whoStarts);
};


template<class P1, class P2>
Game<P1, P2>::Game(Board &board, P1 firstPlayer, P2 secondPlayer, std::string whoStarts)
    : board{ board }, firstPlayer{ firstPlayer }, secondPlayer{ secondPlayer }, playerTurn{ initWhoStarts(whoStarts) } {
        this->firstPlayer.setCrossOrCircle((playerTurn == 1 ? 'X' : 'O'));
        this->secondPlayer.setCrossOrCircle((playerTurn == 2 ? 'X' : 'O'));
    }


template<class P1, class P2>
int Game<P1, P2>::initWhoStarts(std::string whoStarts) {
    if (whoStarts == "None") {
        srand(time(NULL));
        return (rand() % 2) + 1;
    } else if (whoStarts == "p1") {
        return 1;
    } else if (whoStarts == "p2") {
        return 2;
    } else {
        throw "ERROR: Unknown whoStarts attribute!";
    }
}


template<class P1, class P2>
int Game<P1, P2>::play() {
    std::cout << "Player number one is: " << firstPlayer.getCrossOrCircle() 
              << (typeid(firstPlayer) == typeid(HumanPlayer) ? 
                    "\t(Human)" : ("\t(Computer " + firstPlayer.getStringDifficulty() + ")")) << "\n"
              << "Player number two is: " << secondPlayer.getCrossOrCircle()
              << (typeid(secondPlayer) == typeid(HumanPlayer) ? 
                    "\t(Human)" : ("\t(Computer " + secondPlayer.getStringDifficulty() + ")")) << "\n\n";

    Board::MoveType moveType = Board::MoveType::NORMAL;
    while (moveType != Board::MoveType::DRAW && moveType != Board::MoveType::VICTORY) {
        std::cout << board << "\n";

        if (playerTurn == 1) {
            std::array<int, 2> currentMove = firstPlayer.chooseMove();
            moveType = board.makeMove(currentMove[0], currentMove[1], firstPlayer.getCrossOrCircle());
        } else {
            std::array<int, 2> currentMove = secondPlayer.chooseMove();
            moveType = board.makeMove(currentMove[0], currentMove[1], secondPlayer.getCrossOrCircle());
        }

        playerTurn = playerTurn == 1 ? 2 : 1;
    }

    std::cout << board;
    return (moveType == Board::MoveType::DRAW) ? 0 : (playerTurn == 1 ? 2 : 1);
}


#endif // GAME_H