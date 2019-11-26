#include "Game.hpp"

Game::~Game()
{
    for (std::vector<Board *>::iterator i = levels.begin(); i < levels.end(); i++)
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
    sortie << this->hau << "*" << this->lar << "*" << this->levels.size() << std::endl;

    for (std::vector<Board *>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        sortie << (*it)->display() << '#' << std::endl;
    }
    sortie.close();
}

Game::Game(std::string filename)
{
    std::ifstream readFile;
    std::string tmp_str;
    readFile.open(filename);
    if (readFile.is_open())
    {
        getline(readFile, tmp_str);
        std::istringstream ss(tmp_str);
        std::string token;

        getline(ss, token, '*');
        this->hau = stoi(token);
        getline(ss, token, '*');
        this->lar = stoi(token);
        getline(ss, token, '*');
        int nb_level = stoi(token);

        std::string level_string;

        for (int k = 0; k < nb_level; k++)
        {
            std::cout << k << "/" << nb_level << std::endl;
            if (!readFile.eof())
            {
                level_string = "";
                getline(readFile, tmp_str);
                while (tmp_str != "#" && tmp_str != "\n" && !readFile.eof())
                {
                    level_string += tmp_str;
                    getline(readFile, tmp_str);
                }

                std::cout << level_string << "eeeeeeee" << std::endl; // affichage de STRING
                Board a(level_string, hau, lar);
            }
        }
    }
    readFile.close();
}
