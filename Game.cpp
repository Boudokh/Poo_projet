#include "Game.hpp"

Game::~Game(){
    for(std::vector<Board*>::iterator i = boards.begin(); i<boards.end();i++)
    {
        delete *i;
    }
}
