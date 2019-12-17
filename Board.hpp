#ifndef BOARD_HPP
#define BOARD_HPP

#include "Reumus.hpp"
#include "Streumons.hpp"
#include "Object.hpp"
#include "Diams.hpp"
#include "Geurchars.hpp"
#include "Teupor.hpp"
#include "Oueurj.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <time.h>
#include <string>
#include <random>

class Board
{
private:
    int hau;
    int lar;

    class Row
    {
    private:
        friend class Board;
        std::vector<Object *> &row;
        Row(std::vector<Object *> &row) : row(row) {}

    public:
        Object *operator[](size_t i) { return row[i]; }
    };

public:
    Row operator[](size_t i) { return coord[i]; }
    std::vector<std::vector<Object *>> coord;
    Board(int _hau, int _lar, int nb_teupor = 1, int nb_diams = 1, int nb_streumons = 1, int nb_geurchars = 1); //generate random board

    Board(std::string txt_board, int _hau, int _lar);

    std::string display();

    void reumus_vert(int size_max); // génération aléatoire de murs - vertical
    void reumus_hor(int size_max);  // génération aléatoire de murs - horizontal
    void reumus_diag(int size_max); // génération aléatoire de murs - diagonal

    void addDiams(int nb_diams);         // génération aléatoire de diams - au sein du plateau - sans les bords.
    void addGeurchars(int nb_geurchars); // génération aléatoire de geurchars - au sein du plateau - sans les bords.
    void addStreumons(int nb_streumons); // génération aléatoire de streumons - au sein du plateau - sans les bords.

    bool isValid(int row, int col); // Fonction permettant de vérifier si la celulle(row,col) est disponible ou non - déplacement des streumons.
    bool isDest(int row, int col, int x, int y); // Fonction permettant de vérifiant si on arrive à la cellule finale - Position du oueurj (x,y) - A modifié quand class oueurj implémentée.
    double heuristicH(int row, int col, int x, int y); // Fonction heuristique H % à la position du joueur - A modifié quand class oueurj implémentée - distance euclidienne.
    double heuristicManh(int row, int col, int x, int y); // Fonction heuristique calculant la distance de Manhattan


    
    std::vector<int> getRandomPoint();
    void placerOueurj(Oueurj *Oueurj);
    void enleverOuerj(Oueurj *oueurj);

    void openTeupors();

    ~Board();
};

#endif