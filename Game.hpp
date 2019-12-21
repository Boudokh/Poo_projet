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

    bool moveOueurj(char move);
    friend std::vector<int> Board::getRandomPoint();

    bool isValid(int row, int col); // Fonction permettant de vérifier si la celulle(row,col) est disponible ou non. 
    bool isDest(int row, int col); // Fonction permettant de vérifiant si on arrive à la cellule finale.
    double heuristicH(int row, int col); // Fonction heuristique H % à la position du joueur - distance euclidienne. 

    void playStreumons();
    void moveStreumons(int move, int i , int j);



};

#endif