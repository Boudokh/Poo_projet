#ifndef BOARD_HPP
#define BOARD_HPP

#include "Reumus.hpp"
#include "Object.hpp"
#include "Diams.hpp"
#include "Geurchars.hpp"
#include "Teupor.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <time.h>
#include <string>


class Board
{
private:
    int hau;
    int lar;
public:
    std::vector<std::vector<Object *>> coord;
    Board(int _hau, int _lar, int nb_teupor = 1); //generate random board
    Board(std::string txt_board, int _hau, int _lar);
    std::string display();
    ~Board();
    
};

#endif