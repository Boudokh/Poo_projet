#include "Game.hpp"
#include "Board.hpp"
#include <iostream>
#include <regex>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int lar = 30;
    int hau = 15;
    int nb_level = 3;
    int teupor = 10;
    int diam = 5;
    int streum = 6;
    int geurchar = 5;
    //Board* test = new Board(hau, lar, teupor, diam, streum, geurchar);

    //std::cout << *test->[0][0]->getSymbol() << std::endl;

    Game a(hau, lar, nb_level, teupor, diam, streum, geurchar);

    //a.affiche();
    a.to_txt();
    a.play();
    std::string filename = "jeu.txt";
    Game b(filename);

    //b.to_txt();
    //std::cout << test->display() << std::endl;
}
