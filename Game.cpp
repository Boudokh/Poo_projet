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
    init_pos.assign(3, 0);
    plyr = new Oueurj(init_pos);
    placerOueurjRandom();
}

void Game::placerOueurjRandom()
{
    std::vector<int> rd_point;
    std::vector<int> new_pos = plyr->getPos();
    std::cout << new_pos[0] << " " << new_pos[1] << " " << new_pos[2] << std::endl;
    Board &tmp_board = *levels[new_pos[0]];

    while (tmp_board[new_pos[1]][new_pos[2]])
    {
        rd_point = this->levels[0]->getRandomPoint();
        new_pos[1] = rd_point[0], new_pos[2] = rd_point[1];
    }
    plyr->setPos(new_pos);
    this->levels[new_pos[0]]->placerOueurj(plyr);
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
    bool endGame = false;
    do
    {
        nxt_move = getMove();
        endGame = moveOueurj(nxt_move);
        dispCurrLevel();
    } while (nxt_move != 's' && !endGame);
}

bool Game::moveOueurj(char move)
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
        char tmp_sym = tmp_board[new_pos[1]][new_pos[2]]->getSymbol();
        if (tmp_sym == 'X' || tmp_sym == '-')
        {
            std::cout << "impossible" << std::endl;
        }
        else if (tmp_sym == '+')
        {
            this->levels[old_pos[0]]->enleverOuerj(plyr);
            if (old_pos[0] < (int)levels.size() - 1)
            {
                plyr->levelUp();
                std::cout << "teleport" << plyr->getPos()[0] << " " << plyr->getPos()[1] << " " << plyr->getPos()[2] << std::endl;
                placerOueurjRandom();
            }
            else
            {
                std::cout << "gagné" << std::endl;
                return true;
            }
        }
        else
        {
            if (tmp_sym == '$')
            {
                levels[old_pos[0]]->openTeupors();
            }

            if(tmp_sym == 's'){
                plyr->switch_teleport();
            }

            this->levels[old_pos[0]]->enleverOuerj(plyr);
            plyr->setPos(new_pos);
            std::cout << old_pos[0] << " " << old_pos[1] << " " << old_pos[2] << std::endl;
            std::cout << new_pos[0] << " " << new_pos[1] << " " << new_pos[2] << std::endl;
            this->levels[old_pos[0]]->placerOueurj(plyr);
        }
    }
    else
    {
        this->levels[old_pos[0]]->enleverOuerj(plyr);
        plyr->setPos(new_pos);
        std::cout << old_pos[0] << " " << old_pos[1] << " " << old_pos[2] << std::endl;
        std::cout << new_pos[0] << " " << new_pos[1] << " " << new_pos[2] << std::endl;
        this->levels[old_pos[0]]->placerOueurj(plyr);
    }
    return false;
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

double Game::heuristicH(int _row, int _col)
{
    std::vector<int> tmp_pos = plyr->getPos();
    return ((double)sqrt((_row - tmp_pos[1]) * (_row - tmp_pos[1]) + (_col - tmp_pos[2]) * (_col - tmp_pos[2])));
}

bool Game::isValid(int _row, int _col)
{
    std::vector<int> old_pos = plyr->getPos();
    Board &tmp_board = *levels[old_pos[0]];
    return (_row >= 1) && (_row < hau) && (_col >= 1) && (_col < lar) && (tmp_board[_row][_col]->getSymbol()==NULL);
}

bool Game::isDest(int _row, int _col)
{
    std::vector<int> tmp_pos = plyr->getPos();
    if (_row == tmp_pos[1] && _col == tmp_pos[2])
        return true;
    else
        return false;
}

void Game::playStreumons()
{
    std::vector<int> old_pos = plyr->getPos();
    Board &tmp_board = *levels[old_pos[0]];


    for(int i = 1; i < hau; i++)
    {
        for(int j = 1; j < lar; j++)
        {
            if(tmp_board[i][j]->getSymbol()=='s')
            {
                int move = rand() % 8;
                dynamic_cast<Game *>(tmp_board[i][j])->moveStreumons(move,i,j);
                // problème segmentation fault !
            }
        }
    }
}

void Game::moveStreumons(int move, int i , int j)
{
    std::vector<int> old_pos = plyr->getPos();
    Board &tmp_board = *levels[old_pos[0]];
    switch (move)
    {
    case '0': // haut diag gauche
        if(isValid(std::max(0,i-1),std::max(0,j-1)))
        {
            Streumons *tmp_board[std::max(0,i-1)][std::max(0,j-1)] ;
            tmp_board[std::max(0,i-1)][std::max(0,j-1)] = new Streumons();
            tmp_board[i][j] = NULL;
        }
        break;
    case '1': // haut
        if(isValid(std::max(0,i-1),j))
        {
            Streumons *tmp_board[std::max(0,i-1)][j];
            tmp_board[std::max(0,i-1)][j] = new Streumons();
            tmp_board[i][j] = NULL;
        }
        break;
    case '2': // haut diag droite
        if(isValid(std::max(0,i-1),std::min(lar-1,j+1)))
        {
            Streumons *tmp_board[std::max(0,i-1)][std::min(lar-1,j+1)];
            tmp_board[std::max(0,i-1)][std::min(lar-1,j+1)] = new Streumons();
            tmp_board[i][j] = NULL;
        }
        break;
    case '3': // gauche
        if(isValid(i,std::max(0,j-1)))
        {
            Streumons *tmp_board[i][std::max(0,j-1)];
            tmp_board[i][std::max(0,j-1)] = new Streumons();
            tmp_board[i][j] = NULL;
        }
        break;
    case '4' : // droite
        if(isValid(i,std::min(lar-1,j+1)))
        {
            Streumons *tmp_board[i][std::min(lar-1,j+1)];
            tmp_board[i][std::min(lar-1,j+1)] = new Streumons();
            tmp_board[i][j] = NULL;
        }
        break;
    case '5' : // bas
        if(isValid(std::min(hau-1,i+1),j))
        {
            Streumons *tmp_board[std::min(hau-1,i+1)][j];
            tmp_board[std::min(hau-1,i+1)][j] = new Streumons();
            tmp_board[i][j] = NULL;
        }
        break;
    case '6' : // bas diag gauche
        if(isValid(std::min(hau-1,i+1),std::max(0,j-1)))
        {
            Streumons *tmp_board[std::min(hau-1,i+1)][std::max(0,j-1)];
            tmp_board[std::min(hau-1,i+1)][std::max(0,j-1)] = new Streumons();
            tmp_board[i][j] = NULL;
        }
        break;
    case '7' : // bas diag droite
        if(isValid(std::min(hau-1,i+1),std::min(lar-1,j+1)))
        {
            Streumons *tmp_board[std::min(hau-1,i+1)][std::min(lar-1,j+1)];
            tmp_board[std::min(hau-1,i+1)][std::min(lar-1,j+1)] = new Streumons();
            tmp_board[i][j] = NULL;
        }
        break;
    default:
        std::cout << "impossible" << std::endl;
        break;
    }
}
