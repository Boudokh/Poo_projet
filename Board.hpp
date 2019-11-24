#ifndef BOARD_HPP
#define BOARD_HPP

#include "Reumus.hpp"
#include "Object.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <time.h>
#include "Teupor.hpp"

class Board
{
private:
    int hau;
    int lar;
public:
    std::vector<std::vector<Object *>> coord;
    Board(int x, int y, int nb_teupor = 1); //generate random board
    std::string display();
    ~Board();
    
};

#endif