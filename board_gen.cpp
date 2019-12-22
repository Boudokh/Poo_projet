#include "Game.hpp"
#include "Board.hpp"
#include <iostream>
#include <regex>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int lar = 40;
    int hau = 15;
    int nb_level = 1;
    int teupor = 10;
    int diam = 2;
    int streum = 8;
    int geurchar = 3;

    Board *test = new Board(hau, lar, teupor, diam, streum, geurchar);

    Game *a = new Game(hau, lar, nb_level, teupor, diam, streum, geurchar);

    //a.affiche();
    a->affiche();
    a->playStreumons();
    a->affiche();
    //a->to_txt();
    a->play();
    std::string filename = "jeu.txt";
    Game b(filename);

}
