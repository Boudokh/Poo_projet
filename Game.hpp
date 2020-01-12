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

    // Liste des plateaux
    std::vector<Board *> levels;

    // Compteur A* pour streumons.
    int compteurMove;

    // replacer le joueur aléatoirement sur le tableau actuel
    void placerOueurjRandom();

    // déplacer le oueurj
    void move_oueurj(char move);
    // déplacer tous les streumons 
    void play_streumons();

    friend std::vector<int> Board::getRandomPoint();

    // mouvements autorisés à partir de la case (i,j)
    std::vector<std::vector<int>> legalMoves(int i, int j);

    // algorithme de déplacement
    std::vector<int> rand_moves(int i, int j);
    std::vector<int> a_star(int i, int j);
    std::vector<int> a_star_proba(int i, int j, int current_level);

public:
    // constructeur personalisé
    Game(int _hau, int _lar, int nb_level, int nb_teupor = 0, int nb_diams = 1, int nb_streumons = 1, int nb_geurchars = 1);
    // constructeur à partir d'un fichier .game ou .board
    Game(std::string filename);

    ~Game();

    // convertir le tableau en un string
    std::string toString() const;

    // joueur un tour (oueurj puis streumon)
    int play_round(const char move);

    // sauvegarder le plateau sous format de .game ou .board
    void save_game(std::string filename = "jeu");
    void save_boards(std::string filename = "plateau");

};

#endif