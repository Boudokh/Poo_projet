#include "Game.hpp"
#include "Board.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int lar = 15;
    int hau = 10;
    int nb_level = 1;
    int teupor = 3;
    int diam = 5;
    int streum = 6;
    int geurchar = 3;
    Board *test = new Board(hau, lar, teupor, diam, streum, geurchar);

    // Génération des murs intérieurs.

  
    int reumus = rand() % (((lar - 2)) * (hau - 2));
    int size_max = 4;
    int size = (rand() % size_max) + 2;
    Reumus *tmp_str = new Reumus();
    test->reumus_vert(lar, hau, size_max, reumus, tmp_str, test);
    test->reumus_diag(lar, hau, size_max, reumus, tmp_str, test);
    test->reumus_hor(lar, hau, size_max, reumus, tmp_str, test);

    std::cout << test->display() << std::endl;

    Game a(hau, lar, nb_level, teupor, diam, streum, geurchar);
    //a.affiche();
    //a.to_txt();
    a.from_text();
    return 0;
}
