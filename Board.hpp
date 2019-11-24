#ifndef BOARD_HPP
#define BOARD_HPP

#include "Reumus.hpp"
#include "Object.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include "Teupor.hpp"

class Board
{
private:
    int lon;
    int lar;

    std::vector<std::vector<Object *>> coord;

public:
    Board(int x, int y, int nb_teupor = 1); //generate random board
    std::string display();
    ~Board();
    
};

#endif