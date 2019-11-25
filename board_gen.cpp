#include "Game.hpp"
#include "Board.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    Board *test = new Board(8, 10, 200);
    std::cout << test->display() << std::endl;

    Game a(6, 12, 10, 6);
    //a.affiche();
    //a.to_txt();
    a.from_text();
    return 0;
}