#ifndef BOARD_HPP
#define BOARD_HPP

#include "elems/Object.hpp"
class Board
{
private:
    std::vector<std::vector<Object *>> coord;
public:
    Board(); //generate random board
};

#endif