#include "Game.hpp"
#include "Board.hpp"
#include <iostream>
#include <regex>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int lar = 30;
    int hau = 12;
    int nb_level = 3;
    int teupor = 10;

    int diam = 5;
    int streum = 6;
    int geurchar = 5;
    //Board* test = new Board(hau, lar, teupor, diam, streum, geurchar);

    Game *a = new Game(hau, lar, nb_level, teupor, diam, streum, geurchar);
    //a.affiche();
    //a->affiche();
    //a->playStreumons();
    //a->affiche();
    //a->play();
    //a->to_txt();

    std::string filename = "jeu4.txt";
    Game* b= new Game(filename);
    b->to_txt();
    b->play();

    //b.to_txt();
}
