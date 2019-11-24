#include "Game.hpp"

Game::~Game(){
    for (int i=0; i<boards.size(); i++)
    {
        delete [] boards[i];
    }
}

