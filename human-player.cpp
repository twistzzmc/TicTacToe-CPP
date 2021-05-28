#include "human-player.hpp"


std::array<int, 2> HumanPlayer::chooseMove() { 
    int fieldIndex;

    std::cout << "Enter field ID to make a move (you are " << crossOrCircle << "): ";
    std::cin >> fieldIndex;

    while (true) {
        std::array<int, 2> field = { (fieldIndex - 1) / 3, (fieldIndex - 1) % 3 };

        if (fieldIndex < 1 || fieldIndex > 9) {
            std::cout << "Fields have id between 1 and 9. Enter proper ID: ";
            std::cin >> fieldIndex;
        } else if (!board.checkMoveValidity(field[0], field[1])) {
            std::cout << "Field is taken. Enter proper ID: ";
            std::cin >> fieldIndex;
        } else {
            return field;
        }
    }
}
