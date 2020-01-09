#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include <fstream>
#include <limits>
#include <math.h>
#include <chrono>
#include <regex>

class Game
{
private:
    Oueurj *plyr;
    int hau;
    int lar;
    std::string board_name;
    std::vector<Board *> levels;
    int compteurMove; // Compteur aStar pour streumons.

    void generateBoardList();

    void affiche();
    void placerOueurjRandom();
    void dispCurrLevel() const;

    char getMove();
    int get_valid_int();

    bool moveOueurj(char move);
    friend std::vector<int> Board::getRandomPoint();

    void playStreumons();

    std::vector<std::vector<int>> legalMoves(int i, int j);

    std::vector<int> randMoves(int i, int j);
    std::vector<int> aStar(int i, int j);
    std::vector<int> aStarProba(int i, int j, int current_level);

public:
    Game();
    Game(int _hau, int _lar, int nb_level, int nb_teupor = 0, int nb_diams = 1, int nb_streumons = 1, int nb_geurchars = 1);
    Game(std::string filename);

    ~Game();

    std::string toString() const;

    void play();
    int play_round(const char move);

    void save_game(std::string filename = "jeu");
    void save_boards(std::string filename = "plateau");
};

#endif