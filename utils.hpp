#ifndef UTILS_H
#define UTILS_H


#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#include "human-player.hpp"
#include "computer-player.hpp"
#include "game.hpp"


int printOptions(std::string errorMessage);

std::array<std::string, 3> parseOptions(std::vector<std::string> options);

int startGame(std::array<std::string, 3> parsedOptions);


#endif // UTILS_H