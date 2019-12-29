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
    void save_game(std::string filename = "jeu");
    void placerOueurjRandom();
    void dispCurrLevel() const;
    void play();

    char getMove();
    int get_valid_int();

    bool moveOueurj(char move);
    friend std::vector<int> Board::getRandomPoint();

    void playStreumons();

    std::vector<std::vector<int>> legalMoves(int i, int j);

    std::vector<int> randMoves(int i, int j);
    std::vector<int> aStar(int i, int j);
    std::vector<int> aStarProba(int i, int j, int current_level);
};

#endif