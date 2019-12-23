#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <fstream>
#include <sstream>
#include <limits>


class Game
{
private:
    Oueurj *plyr;
    int hau;
    int lar;
    std::vector<Board *> levels;
    int compteurMove = 0; // Compteur aStar pour streumons.


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
    const char getMove();

    void up();
    void down();
    void left();
    void right();

    bool moveOueurj(char move);
    friend const std::vector<int> Board::getRandomPoint();

    void playStreumons();
    void randMoves(int i, int j);
    const std::vector<std::vector<int>> legalMoves(int i, int j);
    void aStar(int i, int j);

};

#endif