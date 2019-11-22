#ifndef BOARD_HPP
#define BOARD_HPP

#include "Reumus.hpp"
#include "Object.hpp"
#include <vector>
#include <iostream>
#include <string>
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
};

#endif