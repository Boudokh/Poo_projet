#include "Game.hpp"
#include <regex>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int lar = 20;
    int hau = 12;
    int nb_level = 5;
    int teupor = 10;
    int diam = 5;
    int streum = 6;
    int geurchar = 5;

    Game *a = new Game(hau, lar, nb_level, teupor, diam, streum, geurchar);

    //a->playStreumons();
    //a->affiche();
    a->play();
    //a->to_txt();

    std::string filename = "jeu.txt";
    Game *b = new Game(filename);
    //b->to_txt();
    //b->play();
}
