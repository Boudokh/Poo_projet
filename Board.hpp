#ifndef BOARD_HPP
#define BOARD_HPP

#include "Reumus.hpp"
#include "Streumons.hpp"
#include "Object.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <time.h>
#include "Teupor.hpp"
#include "Diams.hpp"
#include "Geurchars.hpp"

class Board
{
private:
    int hau;
    int lar;
public:

    std::vector<std::vector<Object *>> coord;
    Board(int x, int y, int nb_teupor = 1, int nb_diams = 1, int nb_streumons = 1, int nb_geurchars = 1); //generate random board
    std::string display();
    void reumus_vert(int _lar, int _hau, int size_max, int reumus, Reumus *tmp_str, Board *test); // génération aléatoire de murs - vertical
    void reumus_hor(int _lar, int _hau, int size_max, int reumus, Reumus *tmp_str, Board *test);  // génération aléatoire de murs - horizontal
    void reumus_diag(int _lar, int _hau, int size_max, int reumus, Reumus *tmp_str, Board *test); // génération aléatoire de murs - diagonal
    ~Board();

};

#endif