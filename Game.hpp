#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <vector>
#include <string>

class Game
{
private:
    std::vector<Board *> boards;

public:
    void generateBoardList();
};

#endif