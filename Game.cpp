#include "Game.hpp"

Game::~Game(){
    for(std::vector<Board*>::iterator i = levels.begin(); i<levels.end();i++)
    {
        delete *i;
    }
}

Game::Game()
{
    int nb_level, nb_teupor;

    std::cout << "nb de niveau?" << std::endl;
    std::cin >> nb_level;
    std::cout << "taille des plateaux? \n longueur ?" << std::endl;
    std::cin >> this->hau;
    std::cout << "largeur?" << std::endl;
    std::cin >> this->lar;
    std::cout << "nombre de teupors?";
    std::cin >> nb_teupor;

    Board *new_level = NULL;

    for (int i = 0; i < nb_level; i++)
    {
        new_level = new Board(this->hau, this->lar, nb_teupor);
        std::cout << new_level->display() << std::endl;
        this->levels.push_back(new_level);
    }
}

Game::Game(int _hau, int _lar, int nb_level, int nb_teupor) : hau(_hau), lar(_lar)
{
    std::cout << "constcting" << std::endl;
    for (int i = 0; i < nb_level; i++)
    {
        this->levels.push_back(new Board(hau, lar, nb_teupor));
    }
}

void Game::affiche()
{
    std::cout << this->levels.at(1)->display() << std::endl;

    for (std::vector<Board *>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        std::cout << (*it)->display() << std::endl;
    }
}

void Game::to_txt()
{
    std::ofstream sortie;
    sortie.open("jeu.txt");
    sortie << this->hau << "*" << this->lar << "|" << this->levels.size() << std::endl;

    for (std::vector<Board *>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        sortie << (*it)->display() << std::endl;
    }
    sortie.close();
}

void Game::to_read()
{
    std::string str;
    std::ifstream readFile;
    readFile.open("jeu.txt");
    if(readFile.is_open())
    {
        while(!readFile.eof)
        {
            getline(readFile,str); // sauvegarder la ligne dans str
            std::cout << str; // affichage de str
        }
    }
    readFile.close();
}