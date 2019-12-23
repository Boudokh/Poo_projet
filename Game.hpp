#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <fstream>
#include <limits>
#include <math.h>
#include <chrono>

class Game
{
private:
    Oueurj *plyr;
    int hau;
    int lar;
    std::vector<Board *> levels;
    int compteurMove; // Compteur aStar pour streumons.

public:
    Game();
    Game(int _hau, int _lar, int nb_level, int nb_teupor = 0, int nb_diams = 1, int nb_streumons = 1, int nb_geurchars = 1);
    Game(std::string filename);

    void generateBoardList();
    ~Game();

    void affiche();
    void to_txt(std::string filename = "jeu");
    void placerOueurjRandom();
    void dispCurrLevel() const;
    void play();
    char getMove();

    void up();
    void down();
    void left();
    void right();

    bool moveOueurj(char move);
    friend std::vector<int> Board::getRandomPoint();

    void playStreumons();
    void randMoves(int i, int j);
    std::vector<std::vector<int>> legalMoves(int i, int j);
    void aStar(int i, int j);
    void aStarProba(int i, int j, int current_level);
    int numberOfStreums();
};

#endif