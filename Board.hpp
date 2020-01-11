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
#include <sstream>
#include <random>
#include <time.h>
#include <string>
#include <random>

class Board
{
private:
    int hau;
    int lar;
    std::vector<std::vector<Object *>> coord;

    // ajout des teupors sur les bords
    void add_teurpors(int nb_teupor);

    // génération aléatoire de murs
    void reumus_vert(int size_max);
    void reumus_hor(int size_max);
    void reumus_diag(int size_max);

    // génération aléatoire d'objets (Streumons, Geurchars, Diams) sur le plateau.
    template <typename T>
    void addItems(int number);

    // classe utilisée pour la surcharge d'opérateur [][]
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
    // opeérateur [i][j], pour accéder directement à l'objet dans la case [i][j]
    Row operator[](size_t i) { return coord[i]; }

    // constructeur à de plateau aléatoire à
    Board(int _hau, int _lar, int nb_teupor = 1, int nb_diams = 1, int nb_streumons = 1, int nb_geurchars = 1);
    // constructeur à partir d'une représentation sous forme de string
    Board(std::string txt_board, int _hau, int _lar);
    ~Board();

    // convertisseur en string, utiles pour l'affichage et l'écriture des fichiers
    std::string toString(bool strm_mode);
    std::stringstream toStream(bool strm_mode);

    // récupèrer les coordonnées d'une case à l'intérieur des bords du plateau
    std::vector<int> getRandomPoint();

    void placer_oueurj(Oueurj *Oueurj);
    void enlever_oueurj(Oueurj *oueurj);

    void open_teupors();

    // déplacer les streumons
    void moveStrm(std::vector<int> old_p, std::vector<int> new_p);

    // calcul de l'heuristique utile pour A*
    double heuristicH(std::vector<int> curr, std::vector<int> dest); // Fonction heuristique H % à la position du joueur - distance euclidienne.

    // interactions de streumons
    void elimination(std::vector<int> old_p, std::vector<int> new_p);
    void reproduction(std::vector<int> old_p, std::vector<int> new_p);
    void fusion(std::vector<int> old_p, std::vector<int> new_p);
};

#endif