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
    char getMove();

    void up();
    void down();
    void left();
    void right();

    bool moveOueurj(char move);
    friend std::vector<int> Board::getRandomPoint();

    void playStreumons();
    void moveStreumons(int move, int i , int j);
    void randMoves(int i, int j);
    std::vector<std::vector<int>> legalMoves(int i, int j);
    void aStar(std::vector<std::vector<int>>, int , int);

    void defendDiams(int,int);
    std::vector<std::vector<int>> legalDefend(int i, int j);


};

#endif