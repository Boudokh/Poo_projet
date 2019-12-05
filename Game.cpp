#include "Game.hpp"

Game::~Game()
{
    for (std::vector<Board *>::iterator i = levels.begin(); i < levels.end(); i++)
    {
        delete *i;
    }
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
        std::cout << hau << "-" << lar << "-" << nb_level << "-" << std::endl;

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

                //std::cout << level_string << "eeeeeeee" << std::endl; // affichage de STRING
                levels.push_back(new Board(level_string, hau, lar));
            }
        }
    }
    readFile.close();
}

Game::Game()
{
    int nb_level, nb_teupor, nb_diams, nb_streumons, nb_geurchars;

    std::cout << "nb de niveau?" << std::endl;
    std::cin >> nb_level;
    std::cout << "taille des plateaux? \n longueur ?" << std::endl;
    std::cin >> this->hau;
    std::cout << "largeur?" << std::endl;
    std::cin >> this->lar;
    std::cout << "nombre de teupors?";
    std::cin >> nb_teupor;
    std::cout << "nb de diams ?" << std::endl;
    std::cin >> nb_diams;
    std::cout << "nb de streumons ?" << std::endl;
    std::cin >> nb_streumons;
    std::cout << "nb de geurchars ?" << std::endl;
    std::cin >> nb_geurchars;

    Board *new_level = NULL;

    for (int i = 0; i < nb_level; i++)
    {
        new_level = new Board(this->hau, this->lar, nb_teupor, nb_diams, nb_streumons);
        //std::cout << new_level->display() << std::endl;
        this->levels.push_back(new_level);
    }
}

Game::Game(int _hau, int _lar, int nb_level, int nb_teupor, int nb_diams, int nb_streumons, int nb_geurchars) : hau(_hau), lar(_lar)
{
    for (int i = 0; i < nb_level; i++)
    {
        this->levels.push_back(new Board(hau, lar, nb_teupor, nb_diams, nb_streumons));
    }

    std::vector<int> init_pos;
    std::vector<int> rd_point;
    init_pos.assign(3, 0);

    Board &tmp_board = *levels[0];

    while (tmp_board[init_pos[1]][init_pos[2]])
    {
        rd_point = this->levels[0]->getRandomPoint();
        init_pos[1] = rd_point[0], init_pos[2] = rd_point[1];
    }
    plyr = new Oueurj(init_pos);
    this->levels[0]->placerOueurj(plyr);
}

void Game::affiche()
{
    for (std::vector<Board *>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        std::cout << (*it)->display() << std::endl;
    }
}

void Game::dispCurrLevel() const
{
    std::cout << this->levels[plyr->getCurrentlevel()]->display() << std::endl;
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

void Game::play()
{
    char nxt_move;
    dispCurrLevel();
    do
    {
        nxt_move = getMove();
        moveOueurj(nxt_move);
        dispCurrLevel();
    } while (nxt_move != 's');
}

void Game::moveOueurj(char move)
{
    std::vector<int> old_pos = plyr->getPos();
    std::vector<int> new_pos = old_pos;
    switch (move)
    {
    case 'a':
        new_pos[1] = std::max(0, old_pos[1] - 1);
        new_pos[2] = std::max(0, old_pos[2] - 1);
        break;
    case 'q':
        new_pos[2] = std::max(0, old_pos[2] - 1);
        break;
    case 'z':
        new_pos[1] = std::max(0, old_pos[1] - 1);
        break;
    case 'd':
        new_pos[2] = std::min(lar - 1, old_pos[2] + 1);
        break;
    case 'x':
        new_pos[1] = std::min(hau - 1, old_pos[1] + 1);
        break;
    case 'c':
        new_pos[1] = std::min(hau - 1, old_pos[1] + 1);
        new_pos[2] = std::min(lar - 1, old_pos[2] + 1);
        break;
    case 'w':
        new_pos[1] = std::min(hau - 1, old_pos[1] + 1);
        new_pos[2] = std::max(0, old_pos[2] - 1);
        break;
    case 'e':
        new_pos[1] = std::max(0, old_pos[1] - 1);
        new_pos[2] = std::min(lar - 1, old_pos[2] + 1);
        break;
    }
    Board &tmp_board = *levels[old_pos[0]];

    if (tmp_board[new_pos[1]][new_pos[2]])
    {
        if (tmp_board[new_pos[1]][new_pos[2]]->getSymbol() == 'X' || tmp_board[new_pos[1]][new_pos[2]]->getSymbol() == '-')
        {
            std::cout << "impossible" << std::endl;
        }
        else
        {
            plyr->setPos(new_pos);
            std::cout << old_pos[0] << " " << old_pos[1] << " " << old_pos[2] << std::endl;
            std::cout << new_pos[0] << " " << new_pos[1] << " " << new_pos[2] << std::endl;
            this->levels[old_pos[0]]->placerOueurj(plyr);
        }
    }
    else
    {
        plyr->setPos(new_pos);
        std::cout << old_pos[0] << " " << old_pos[1] << " " << old_pos[2] << std::endl;
        std::cout << new_pos[0] << " " << new_pos[1] << " " << new_pos[2] << std::endl;
        this->levels[old_pos[0]]->placerOueurj(plyr);
    }
}

char Game::getMove()
{
    char nxt_move;
    std::string legal_moves = "azeqsdwxc";
    do
    {
        nxt_move = std::cin.get();
    } while (legal_moves.find(nxt_move) == std::string::npos);

    return nxt_move;
}