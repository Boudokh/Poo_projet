#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <fstream>
#include <sstream>

class Game
{
private:
    int current_level;
    int hau;
    int lar;
    std::vector<Board *> levels;

public:
    Game();
    Game(int _hau, int _lar, int nb_level, int nb_teupor = 0);
    void generateBoardList();
    ~Game();
    void affiche();
    void to_txt();
    Game(std::string filename);
};

#endif