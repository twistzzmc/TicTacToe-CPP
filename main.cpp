#include <iostream>
#include <algorithm>

#include "utils.hpp"


int main(int argc, char * argv[])
{
    std::vector<std::string> options{ argv + 1, argv + argc };

    /* opponent, player, startingPlayer */
    std::array<std::string, 3> parsedOptions = parseOptions(options);

    if (parsedOptions[0] == "")
        return printOptions(parsedOptions[1]);

    int winner = startGame(parsedOptions);
    

    std::string firstPlayer, secondPlayer;

    if (parsedOptions[0] == "human" || parsedOptions[0] == "None")
        firstPlayer = "human";
    else
        firstPlayer = "computer - " + parsedOptions[0];

    if (parsedOptions[1] == "human" || parsedOptions[1] == "None")
        secondPlayer = "human";
    else
        secondPlayer = "computer - " + parsedOptions[1];


    switch (winner) {
    case 0:
        std::cout << "\nDRAW! (between " << firstPlayer << " and " << secondPlayer << ")\n";
        break;
    case 1:
        std::cout << "\nWINNER IS PLAYER #" << winner << "(" << firstPlayer << ")\n";
        break;
    case 2:
        std::cout << "\nWINNER IS PLAYER #" << winner << "(" << secondPlayer << ")\n";
        break;
    }

    return 0;
}


