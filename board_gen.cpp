#include "Game.hpp"
#include <regex>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int lar = 30;
    int hau = 5;
    int nb_level = 100;
    int teupor = 10;
    int diam = 0;
    int streum = 0;
    int geurchar = 0;

    Game *a = new Game(hau, lar, nb_level, teupor, diam, streum, geurchar);
    a->affiche();
}
