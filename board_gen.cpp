#include "Game.hpp"
#include "Board.hpp"
#include <iostream>
#include <regex>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    Board *test = new Board(8, 10, 200);
    std::cout << test->display() << std::endl;

    Game a(5, 7, 5, 6);
    //a.affiche();
    //a.to_txt();

    Game b("jeu.txt");


}