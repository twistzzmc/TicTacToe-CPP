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
            if (checkForWin(line, crossOrCircle)) {
                winningMoves.push_back(i);
                break;
            }
            else if (checkForWin(line, (crossOrCircle == 'X' ? 'O' : 'X'))) {
                opponentCouldWinMoves.push_back(i);
                break;
            }
            else {
                normalMoves.push_back(i);
                break;
            }
        }
    }


    int pickGoodMoveChance = getGoodMoveOdds();

    std::array<int, 2> move;
    int fieldIndex;
    srand(time(NULL));

    if (winningMoves.size() > 0 && rand() % 101 < pickGoodMoveChance) {
        fieldIndex = winningMoves[rand() % winningMoves.size()];
    } else if (opponentCouldWinMoves.size() > 0 && rand() % 101 < pickGoodMoveChance) {
        fieldIndex = opponentCouldWinMoves[rand() % opponentCouldWinMoves.size()];
    } else if (normalMoves.size() > 0) {
        fieldIndex = pickNormalMoveFieldIndexBasedOnDifficulty(normalMoves);
    } else {
        if (opponentCouldWinMoves.size() != 0)
            fieldIndex = opponentCouldWinMoves[rand() % opponentCouldWinMoves.size()];
        else
            fieldIndex = winningMoves[rand() % winningMoves.size()];
    }

    move = { fieldIndex / 3, fieldIndex % 3 };

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


int ComputerPlayer::getGoodMoveOdds() const {
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

    return pickGoodMoveChance;
}


int ComputerPlayer::pickNormalMoveFieldIndexBasedOnDifficulty(std::vector<int> normalMoves) const {
    std::set<int> moveIndexesToLookFor;
    int goodMoveChance = getGoodMoveOdds();
    
    srand(time(NULL));

    // middle field
    if (rand() % 101 < goodMoveChance)
        moveIndexesToLookFor = std::set<int>{ 5 };

    // corner fields
    else if (rand() % 101 < goodMoveChance)
        moveIndexesToLookFor = std::set<int>{ 1, 3, 7, 9 };

    // rest of the fields
    else
        moveIndexesToLookFor = std::set<int>{ 2, 4, 6, 8 };


    for (auto normalMove : normalMoves) {
        if (moveIndexesToLookFor.find(normalMove + 1) != moveIndexesToLookFor.end())
            return normalMove;
    }

    return normalMoves[rand() % normalMoves.size()];
}
