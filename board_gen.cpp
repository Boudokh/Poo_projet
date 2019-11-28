#include "Game.hpp"
#include "Board.hpp"
#include <iostream>
#include <regex>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    Board *test = new Board(4, 5, 4);
    std::cout << test->display() << std::endl;

    Game a(4,5, 3, 6);
    //a.affiche();
    //a.to_txt();
    std::string filename = "jeu.txt";
    Game b = Game(filename);
    //b.affiche();
    //b.to_txt();
}