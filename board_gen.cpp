#include "Game.hpp"
#include <regex>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int lar = 50;
    int hau = 20;
    int nb_level = 5;
    int teupor = 10;
    int diam = 5;
    int streum = 4;
    int geurchar = 5;

    Game *a = new Game(hau, lar, nb_level, teupor, diam, streum, geurchar);

    //a->playStreumons();
    //a->affiche();
    //a->save_boards("aa");
    //a->play();
    //a->save_game("aaa");
    //a->save_game();

    Game *b = new Game("aa.board");
    //b->save_game();
    b->play();
    b = new Game("aaa.game");
    b->play();
}
