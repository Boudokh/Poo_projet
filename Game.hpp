#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <fstream>
#include <sstream>

class Game
{
private:
    Oueurj *plyr;
    int hau;
    int lar;
    std::vector<Board *> levels;

public:
    Game();
    Game(int _hau, int _lar, int nb_level, int nb_teupor = 0, int nb_diams = 1, int nb_streumons = 1, int nb_geurchars = 1);
    Game(std::string filename);

    void generateBoardList();
    ~Game();

    void affiche();
    void to_txt();
    void placerOueurjRandom();
    void dispCurrLevel() const;
    void play();
    char getMove();

    void up();
    void down();
    void left();
    void right();

    void moveOueurj(char move);
    friend std::vector<int> Board::getRandomPoint();
};

#endif