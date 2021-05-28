#include "utils.hpp"


int printOptions(std::string errorMessage) {
    if (errorMessage != "")
        std::cout << errorMessage << "\n\n";

    std::cout << "Usage: ./tictactoe -p [ PLAYER ] [ OPTIONS ]\n"
              << "OPTIONS\n"
              << "\t-p, --player\n"
              << "\t\tSets your opponent. Necessary option. Possible values: human, easy, medium, hard.\n"
              << "\t\tWhere other than human is a computer on different difficulty levels.\n"

              << "\n\t-p2, --second-player\n"
              << "\t\tOptional specification of second player. Options like for first player.\n"
              << "\t\tBy default it is set to player (you).\n"

              << "\n\t-s, --start\n"
              << "\t\tWho has the first move. Values: opponent, me. Where opponent is --player\n"
              << "\t\tand me is player two from --second-player (by default you).\n"

              << "\n\t-h, --help\n"
              << "\t\tPrints options.\n";

    return 0;
}


std::array<std::string, 3> parseOptions(std::vector<std::string> options) {
    std::string firstPlayer = "None", secondPlayer = "None", startingPlayer = "None";

    
    for (auto it = options.begin(); it != options.end(); it++) {
        if (*it == "-p" || *it == "--player") {
            it++;
            if (it != options.end() && (*it == "human" || *it == "easy" || *it == "medium" || *it == "hard")) {
                firstPlayer = *it;
            } else if (it != options.end()) {
                return std::array<std::string, 3>{ "", std::string{ "Bad option for --player: " + *it }, "" };
            } else {
                return std::array<std::string, 3>{ "", std::string{ "--player argument not specified!" }, "" };
            }
        } else if (*it == "-p2" || *it == "--second-player") {
            it++;
            if (it != options.end() && (*it == "human" || *it == "easy" || *it == "medium" || *it == "hard")) {
                secondPlayer = *it;
            } else if (it != options.end()) {
                return std::array<std::string, 3>{ "", std::string{ "Bad option for --second-player: " + *it }, "" };
            } else {
                return std::array<std::string, 3>{ "", std::string{ "--second-player argument not specified!" }, "" };
            }
        } else if (*it == "-s" || *it == "--start") {
            it++;
            if (it != options.end() && (*it == "p1" || *it == "p2")) {
                startingPlayer = *it;
            } else if (it != options.end()) {
                return std::array<std::string, 3>{ "", std::string{ "Bad option for --start: " + *it }, "" };
            } else {
                return std::array<std::string, 3>{ "", std::string{ "--start argument not specified!" }, "" };
            }
        } else if (*it == "-h" || *it == "--help") {
            return std::array<std::string, 3>{ "", "", "" };
        } else {
            return std::array<std::string, 3>{ "", std::string{ "Bad option: " + *it }, "" };
        }
    }

    if (firstPlayer == "None")
        return std::array<std::string, 3>{ "", std::string{ "Option --player not specified!" }, "" };

    return std::array<std::string, 3>{ firstPlayer, secondPlayer, startingPlayer };
}


int startGame(std::array<std::string, 3> parsedOptions) {
    std::string opponent = parsedOptions[0], player = parsedOptions[1], startingPlayer = parsedOptions[2];

    Board board{ };

    if (opponent == "human" && (player == "None" || player == "human")) {
        Game<HumanPlayer, HumanPlayer> game { 
            board, 
            HumanPlayer{ board }, 
            HumanPlayer{ board }, 
            startingPlayer 
        };

        return game.play();
    } else if (opponent == "human") {
        Game<HumanPlayer, ComputerPlayer> game{ 
            board, 
            HumanPlayer{ board }, 
            ComputerPlayer{ board, player }, 
            startingPlayer 
        };

        return game.play();
    } else if (player == "None" || player == "human") {
        Game<ComputerPlayer, HumanPlayer> game{ 
            board, 
            ComputerPlayer{ board, opponent }, 
            HumanPlayer{ board }, 
            startingPlayer 
        };

        return game.play();
    } else {
        Game<ComputerPlayer, ComputerPlayer> game{ 
            board, 
            ComputerPlayer{ board, opponent }, 
            ComputerPlayer{ board, player }, 
            startingPlayer 
        };
        
        return game.play();
    }
}
