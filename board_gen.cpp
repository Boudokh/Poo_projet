#include "Game.hpp"
#include "Board.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    Board *test = new Board(10, 10, 100);
    std::cout << typeid(test).name() <<std::endl;
    std::cout << test->display() << std::endl;
    return 0;
}