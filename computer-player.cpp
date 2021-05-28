#include "computer-player.hpp"


std::array<int, 2> ComputerPlayer::chooseMove() {
    std::cout << "Computer is making move... ";

    std::vector<int> winningMoves;
    std::vector<int> opponentCouldWinMoves;
    std::vector<int> normalMoves;

    for (int i = 0; i < 9; i++) {
        int x = i / 3, y = i % 3;

        if (!board.checkMoveValidity(x, y))
            continue;

        for (auto line : board.getRelevantLines(x, y)) {
            if (checkForWin(line, crossOrCircle))
                winningMoves.push_back(i);
            else if (checkForWin(line, (crossOrCircle == 'X' ? 'O' : 'X')))
                opponentCouldWinMoves.push_back(i);
            else
                normalMoves.push_back(i);
        }
    }

    int pickGoodMoveChance;
    switch (difficulty) {
    case Difficulty::EASY:
        pickGoodMoveChance = 33;
        break;
    case Difficulty::MEDIUM:
        pickGoodMoveChance = 66;
        break;
    case Difficulty::HARD:
        pickGoodMoveChance = 99;
        break;
    }

    std::array<int, 2> move;
    int fieldIndex, moveIndex;
    srand(time(NULL));

    if ((winningMoves.size() > 0 && rand() % 101 < pickGoodMoveChance) || normalMoves.size() == 0) {
        moveIndex = rand() % winningMoves.size();
        fieldIndex = winningMoves[moveIndex];
        move = { winningMoves[moveIndex] / 3, winningMoves[moveIndex] % 3 };
    } else if ((opponentCouldWinMoves.size() > 0 && rand() % 101 < pickGoodMoveChance) || normalMoves.size() == 0) {
        moveIndex = rand() % opponentCouldWinMoves.size();
        fieldIndex = opponentCouldWinMoves[moveIndex];
        move =  { opponentCouldWinMoves[moveIndex] / 3, opponentCouldWinMoves[moveIndex] % 3 };
    } else {
        moveIndex = rand() % normalMoves.size();
        fieldIndex = normalMoves[moveIndex];
        move =  { normalMoves[moveIndex] / 3, normalMoves[moveIndex] % 3 };
    }

    std::cout << "Computer chose field with index: " << fieldIndex + 1 << "\n";
    return move;
}


std::string ComputerPlayer::getStringDifficulty() const {
    switch (difficulty) {
    case Difficulty::EASY:
        return "easy";
    case Difficulty::MEDIUM:
        return "medium";
    case Difficulty::HARD:
        return "hard";
    
    default:
        throw "ERROR: unknown difficulty";
    }
}


ComputerPlayer::Difficulty ComputerPlayer::initDifficulty(std::string difficulty) {
    if (difficulty == "easy")
        return ComputerPlayer::Difficulty::EASY;
    if (difficulty == "medium")
        return ComputerPlayer::Difficulty::MEDIUM;
    if (difficulty == "hard")
        return ComputerPlayer::Difficulty::HARD;

    srand(time(NULL));
    switch (rand() % 3) {
    case 0:
        return ComputerPlayer::Difficulty::EASY;
    case 1:
        return ComputerPlayer::Difficulty::MEDIUM;
    case 2:
        return ComputerPlayer::Difficulty::HARD;
    }

    throw "ERROR: Unknown difficulty!";
}


bool ComputerPlayer::checkForWin(std::array<char, 3> line, char symbol) {
    int spacesCount = 0, xCount = 0, oCount = 0;

    for (int i = 0; i < 3; i++) {
        switch (line[i]) {
        case ' ':
            spacesCount++;
            break;
        case 'X':
            xCount++;
            break;
        case 'O':
            oCount++;
            break;
        }
    }

    if (spacesCount == 1 && ((symbol == 'X' && xCount == 2) || (symbol == 'O' && oCount == 2)))
        return true;
    
    return false;
}
