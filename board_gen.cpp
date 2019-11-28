#include "Game.hpp"
#include "Board.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int lar = 40;
    int hau = 15;
    int nb_level = 1;
    int teupor = 10;
    int diam = 5;
    int streum = 6;
    int geurchar = 3;
    Board *test = new Board(hau, lar, teupor, diam, streum, geurchar);

    // Génération des murs intérieurs.

    // Affichage du plateau de jeu

    std::cout << test->display() << std::endl;

    Game a(hau, lar, nb_level, teupor, diam, streum, geurchar);
    //a.affiche();
    //a.to_txt();
    return 0;
}
