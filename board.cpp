#include "board.hpp"


std::ostream& operator<<(std::ostream &out, const Board &board) {
    auto rowWithFields = [](const char fields[3]) {
        return (std::string{ " " } + fields[0] + " | " + fields[1] + " | " + fields[2]);
    };

    std::string rowWithoutFields = "———|———|———";
    std::string tabs = "\t\t\t\t\t";
    std::string spaces = "            ";

    const char firstRowIndexes[3] = { '1', '2', '3' };
    const char secondRowIndexes[3] = { '4', '5', '6' };
    const char thirdRowIndexes[3] = { '7', '8', '9' };

    /*
    Empty board as a string:

        "   |   |   \t\t\t\t\tField ID's:  1 | 2 | 3 \n"
        "———|———|———\t\t\t\t\t            ———|———|———\n"
        "   |   |   \t\t\t\t\t             4 | 5 | 6 \n"
        "———|———|———\t\t\t\t\t            ———|———|———\n"
        "   |   |   \t\t\t\t\t             7 | 8 | 9 \n";
    */

    return out << rowWithFields(board.fields[0]) << tabs << "Field ID's  " << rowWithFields(firstRowIndexes) << "\n"
               << rowWithoutFields << tabs << spaces << rowWithoutFields << "\n"
               << rowWithFields(board.fields[1]) << tabs << spaces << rowWithFields(secondRowIndexes) << "\n"
               << rowWithoutFields << tabs << spaces << rowWithoutFields << "\n"
               << rowWithFields(board.fields[2]) << tabs << spaces << rowWithFields(thirdRowIndexes) << "\n";
}


std::ostream& operator<<(std::ostream &out, const Board::MoveType &moveType) {
    switch (moveType) {
    case Board::MoveType::NORMAL:
        return out << "NORMAL";
    case Board::MoveType::VICTORY:
        return out << "Victory";
    case Board::MoveType::DRAW:
        return out << "DRAW";
    case Board::MoveType::NOT_ALLOWED:
        return out << "NOT_ALLOWED";
    case Board::MoveType::WRONG_TURN:
        return out << "WRONG_TURN";
    }

    throw "ERROR: unknown move type!";
}


Board::MoveType Board::makeMove(int x, int y, char playerChar) {
    if (fields[x][y] != ' ' || (playerChar != 'X' && playerChar != 'O')) 
        return MoveType::NOT_ALLOWED;

    if ((playerChar == 'X' && movesCount % 2 == 1) || (playerChar == 'O' && movesCount % 2 == 0))
        return MoveType::WRONG_TURN; 

    fields[x][y] = playerChar;
    moves[movesCount] = std::pair<std::array<int, 2>, char>{ std::array<int, 2>{ x, y }, playerChar };
    movesCount++;
    return checkBoardStatusAfterMove(x, y);
}

std::vector<std::array<char, 3>> Board::getRelevantLines(int x, int y) {
    std::vector<std::array<char, 3>> relevantLines;

    relevantLines.push_back(getLine(Direction::VERTICAL, x));
    relevantLines.push_back(getLine(Direction::HORIZONTAL, y));

    bool forward = false, backward = false;

    if (x % 2 == 0 && y % 2 == 0) {
        if (x == y) backward = true;
        if (x != y) forward = true;
    } else if (x == 1 && y == 1) {
        forward = true;
        backward = true;
    }

    if (forward)    relevantLines.push_back(getLine(Direction::FORWARD_SLASH));
    if (backward)   relevantLines.push_back(getLine(Direction::BACKWARD_SLASH));

    return relevantLines;
}

Board::MoveType Board::checkBoardStatusAfterMove(int x, int y) {
    std::vector<std::array<char, 3>> linesToCheck = getRelevantLines(x, y);

    for (std::array<char, 3> line : linesToCheck) {
        if ((line[0] == 'X' || line[0] == 'O') && line[0] == line[1] && line[1] == line[2])
            return MoveType::VICTORY;
    }

    if (movesCount == 9)
        return MoveType::DRAW;

    return MoveType::NORMAL;
}

std::array<char, 3> Board::getLine(Direction direction, int index) const {
    switch (direction) {
    case Direction::VERTICAL:
        return std::array<char, 3>{ fields[index][0], fields[index][1], fields[index][2] };
    case Direction::HORIZONTAL:
        return std::array<char, 3>{ fields[0][index], fields[1][index], fields[2][index] };
    case Direction::FORWARD_SLASH:
        return std::array<char, 3>{ fields[2][0], fields[1][1], fields[0][2] };
    case Direction::BACKWARD_SLASH:
        return std::array<char, 3>{ fields[0][0], fields[1][1], fields[2][2] };
    }

    throw "ERROR: unknown Direction!";
}
