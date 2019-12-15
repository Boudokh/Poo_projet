#include "Game.hpp"
#include "Board.hpp"
#include <iostream>
#include <regex>

int main(int argc, char *argv[])
{
    srand(time(NULL));
  
    int lar = 40;
    int hau = 15;
    int nb_level = 5;
    int teupor = 10;
    int diam = 5;
    int streum = 6;
    int geurchar = 3;
    Board *test = new Board(hau, lar, teupor, diam, streum, geurchar);

    /* Test Uniforme - Random generator

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,6);
    int dice_roll = distribution(generator); // generate number in range 1 to 6

    auto dice = std::bind(distribution, generator);
    int wisdom = dice()+dice()+dice();
    */


    std::cout << test->display() << std::endl;

    Game a(hau, lar, nb_level, teupor, diam, streum, geurchar);
    //a.affiche();
    a.to_txt();
    std::string filename = "jeu.txt";
    Game b(filename);

    std::cout << "Validité (i,j) : " << test->isValid(3,5) << std::endl;
    std::cout << "Destination : " << test->isDest(3,5,4,5) << std::endl;
    std::cout << "Heuristique h : " << test->heuristicH(3,5,10,10) << std::endl;
    std::cout << "Heuristique Manhattan : " << test->heuristicManh(3,5,10,10) << std::endl;

    /* Test déplacement des streumons */

    int move = (rand()%8)+1;
    b.affiche();
}

