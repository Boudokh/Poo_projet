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
    Board(int _hau, int _lar, int nb_teupor = 1, int nb_diams = 1, int nb_streumons = 1, int nb_geurchars = 1); //generate random board
    std::string display();

    void reumus_vert(int size_max); // génération aléatoire de murs - vertical
    void reumus_hor(int size_max);  // génération aléatoire de murs - horizontal
    void reumus_diag(int size_max); // génération aléatoire de murs - diagonal

    void addDiams(int nb_diams);         // génération aléatoire de diams - au sein du plateau - sans les bords.
    void addGeurchars(int nb_geurchars); // génération aléatoire de geurchars - au sein du plateau - sans les bords.
    void addStreumons(int nb_streumons); // génération aléatoire de streumons - au sein du plateau - sans les bords.

    std::vector<int> getRandomPoint();
    ~Board();
};

#endif