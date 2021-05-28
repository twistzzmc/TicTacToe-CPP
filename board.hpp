#ifndef BOARD_H
#define BOARD_H


#include <iostream>
#include <vector>
#include <array>


class Board {
    public:
        /* VERTICAL (|), HORIZONTAL (—), FORWARD_SLASH (/), BACKWARD_SLASH (\) */
        enum class Direction { VERTICAL, HORIZONTAL, FORWARD_SLASH, BACKWARD_SLASH };

        enum class MoveType { NORMAL, VICTORY, DRAW, NOT_ALLOWED, WRONG_TURN };

    private:
        char fields[3][3];
        size_t movesCount; /* X always starts first -> if (movesCount % 2 == 0) X moves */
        std::pair<std::array<int, 2>, char> moves[9];

    public:
        Board() : movesCount{ 0 }, moves{ } { std::fill(&fields[0][0], &fields[0][0] + sizeof(fields), ' '); }

        Board(const Board& temp_obj) = delete;
        Board& operator=(const Board& temp_obj) = delete;

        friend std::ostream& operator<<(std::ostream &out, const Board &Board);
        friend std::ostream& operator<<(std::ostream &out, const Board::MoveType &moveType);

        MoveType makeMove(int x, int y, char playerChar);
        bool checkMoveValidity(int x, int y) const { return fields[x][y] == ' '; }
        
        char getField(int x, int y) const { return fields[x][y]; }
        size_t getMovesCount() const { return movesCount; }
        std::pair<std::array<int, 2>, char>* getMoves() { return moves; }
        std::vector<std::array<char, 3>> getRelevantLines(int x, int y);

    private:
        MoveType checkBoardStatusAfterMove(int x, int y);
        std::array<char, 3> getLine(Direction direction, int index=0) const;
};


#endif // BOARD_H