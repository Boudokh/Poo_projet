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
    std::vector<int> init_pos;

    this->compteurMove = 0;

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

        for (int i = 0; i < 3; i++)
        {
            getline(ss, token, '*');
            init_pos.push_back(stoi(token));
        }
        std::string telep;
        getline(ss, telep, '*');

        getline(ss, token, '*');
        int nb_diams = stoi(token);

        if (telep == "inf")
        {
            plyr = new Oueurj(init_pos, nb_diams, true);
        }
        else
        {
            plyr = new Oueurj(init_pos, nb_diams, false, stoi(telep));
        }

        std::string level_string;
        level_string.reserve(this->hau * this->lar);

        for (int k = 0; k < nb_level; k++)
        {
            if (!readFile.eof())
            {
                level_string = "";
                getline(readFile, tmp_str);
                while (tmp_str != "#" && tmp_str != "\n" && !readFile.eof())
                {
                    level_string += tmp_str;
                    getline(readFile, tmp_str);
                }

                levels.push_back(new Board(level_string, hau, lar));
            }
        }
    }
    readFile.close();
}

Game::Game()
{
    int nb_level, nb_teupor, nb_diams, nb_streumons, nb_geurchars;
    this->compteurMove = 0;

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
        this->levels.push_back(new_level);
    }
}

Game::Game(int _hau, int _lar, int nb_level, int nb_teupor, int nb_diams, int nb_streumons, int nb_geurchars) : hau(_hau), lar(_lar)
{
    this->compteurMove = 0;

    for (int i = 0; i < nb_level; i++)
    {
        this->levels.push_back(new Board(hau, lar, nb_teupor, nb_diams, nb_streumons, nb_geurchars));
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
    Board &tmp_board = *levels[new_pos[0]];
    bool keep_search = true;

    while (keep_search)
    {
        rd_point = this->levels[new_pos[0]]->getRandomPoint();
        new_pos[1] = rd_point[0], new_pos[2] = rd_point[1];
        if (tmp_board[new_pos[1]][new_pos[2]] == NULL)
            keep_search = false;
    }

    plyr->setPos(new_pos);
    this->levels[new_pos[0]]->placerOueurj(plyr);
}

void Game::affiche()
{
    for (std::vector<Board *>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        std::cout << (*it)->toString() << std::endl;
    }
}

void Game::dispCurrLevel() const
{
    std::stringstream level_strm = this->levels[plyr->getCurrentlevel()]->toStream();
    std::stringstream plyr_info = plyr->toStream();

    std::string tmp_str;

    for (int i = 0; i < hau; i++)
    {
        getline(level_strm, tmp_str);
        std::cout << tmp_str;
        tmp_str.clear();
        getline(plyr_info, tmp_str);
        std::cout << tmp_str;
        if (i == 2)
        {
            std::cout << "/" << this->levels.size();
        }
        std::cout << std::endl;
    }
}

void Game::to_txt(std::string filename)
{
    std::ofstream sortie;
    sortie.open(filename + ".txt");

    char sep = '*';
    sortie << this->hau << sep << this->lar << sep << this->levels.size() << sep;
    std::vector<int> plyr_pos = plyr->getPos();

    for (unsigned int i = 0; i < plyr_pos.size(); i++)
    {
        sortie << plyr_pos[i] << sep;
    }
    sortie << plyr->getTelep() << sep << plyr->getNbDiams() << sep << std::endl;

    for (std::vector<Board *>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        sortie << (*it)->toString() << '#' << std::endl;
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

        playStreumons();
        dispCurrLevel();
    } while (nxt_move != 's' && !endGame && plyr->getState() == 0);

    if (plyr->getState() == 1)
    {
        std::cout << "VICTOIRE" << std::endl;
    }
    else if (plyr->getState() == -1)
    {
        std::cout << "DEFAITE" << std::endl;
    }
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
    case 't':
        if (plyr->teleport())
        {
            this->levels[old_pos[0]]->enleverOuerj(plyr);
            plyr->setPos(new_pos);
            placerOueurjRandom();
        }
        return false;
    }
    Board &tmp_board = *levels[old_pos[0]];

    if (tmp_board[new_pos[1]][new_pos[2]])
    {
        char tmp_sym = tmp_board[new_pos[1]][new_pos[2]]->getSymbol();
        if (tmp_sym == 's')
        {
            plyr->die();
            //std::cout << "lost" << std::endl;
            return true;
        }
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
                std::cout << "levelup" << plyr->getPos()[0] << " " << plyr->getPos()[1] << " " << plyr->getPos()[2] << std::endl;
                placerOueurjRandom();
            }
            else
            {
                plyr->win();
                //std::cout << "gagné" << std::endl;
                return true;
            }
        }
        else
        {
            if (tmp_sym == '$')
            {
                delete (tmp_board[new_pos[1]][new_pos[2]]);
                plyr->eatDiams();
                levels[old_pos[0]]->openTeupors();
            }

            if (tmp_sym == '*')
            {
                delete (tmp_board[new_pos[1]][new_pos[2]]);
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
    std::string legal_moves = "azeqsdwxct";
    do
    {
        nxt_move = std::cin.get();
    } while (legal_moves.find(nxt_move) == std::string::npos);

    return nxt_move;
}

void Game::playStreumons()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> plyr_p = plyr->getPos();
    Board &curr_board = *levels[plyr_p[0]];

    std::vector<int> new_pos, old_pos;
    std::string symb_list = curr_board.toString();

    for (int i = 0; i < hau; i++)
    {
        for (int j = 0; j < lar; j++)
        {
            if (symb_list[i * (lar + 1) + j] == 's')
            {
                switch (dynamic_cast<Streumons *>(curr_board[i][j])->getType())
                {
                case 0:
                    new_pos = randMoves(i, j);
                    break;
                case 1:
                    new_pos = aStar(i, j);
                    break;
                case 2:
                    new_pos = aStarProba(i, j, plyr_p[0]);
                    break;
                default:
                    break;
                }

                old_pos = {i, j};
                curr_board.moveStrm(old_pos, new_pos);
                if (new_pos[0] == plyr_p[1] && new_pos[1] == plyr_p[2])
                {
                    this->plyr->die();
                }
                if(symb_list[new_pos[0] * (lar + 1) + new_pos[1]] == 's')
                {
                    switch (dynamic_cast<Streumons *>(curr_board[i][j])->getTypeEvol())
                    {
                    case 0:
                        std::cout << "elimination de streums en cours" << std::endl;
                        elimination(old_pos,new_pos);
                        break;
                    //case 1:
                        //std::cout << "reproduction de streums en cours " << std::endl;
                        //reproduction(old_pos,new_pos);
                    default:
                        break;
                    }
                }
            }
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
}

std::vector<std::vector<int>> Game::legalMoves(int i, int j)
{
    std::vector<int> plyr_p = plyr->getPos();
    std::vector<int> old_pos{i, j};

    Board &tmp_board = *levels[plyr_p[0]];

    std::vector<std::vector<int>> legal_moves;
    std::vector<int> tmp_move;

    for (int x = std::max(1, i - 1); x <= std::min(hau - 1, i + 1); x++)
    {
        for (int y = std::max(1, j - 1); y <= std::min(lar - 1, j + 1); y++)
        {
            if (tmp_board[x][y] == NULL && (x != i || y != j))
            {
                tmp_move = {x, y};
                legal_moves.push_back(tmp_move);
            }
            else if (tmp_board[x][y]->getSymbol() == 'J')
            {
                tmp_move = {x, y};
                legal_moves.push_back(tmp_move);
            }
        }
    }

    return legal_moves;
}

std::vector<int> Game::randMoves(int i, int j)
{
    std::vector<int> plyr_p = plyr->getPos();
    std::vector<int> old_pos{i, j};

    std::vector<std::vector<int>> legal_moves = legalMoves(i, j);

    //levels[plyr_p[0]]->moveStrm(old_pos, legal_moves[rand() % legal_moves.size()]);
    return legal_moves[rand() % legal_moves.size()];
}

std::vector<int> Game::aStar(int i, int j)
{
    std::vector<std::vector<int>> moves = legalMoves(i, j);
    std::vector<double> tmp_score; // vecteur permettant de stocker les heuristiques (distance à vol d'oiseau) pour les cases choisies (valides) à la destination finale.
    std::vector<int> plyr_p = plyr->getPos();
    std::vector<int> new_pos;
    std::vector<int> old_pos = {i, j};

    Board &tmp_board = *levels[plyr_p[0]];

    double minHeuristic = std::numeric_limits<double>::infinity();
    double score;

    for (unsigned int i = 0; i < moves.size(); i++)
    {
        score = compteurMove + tmp_board.heuristicH(moves[i], plyr_p);
        tmp_score.push_back(score);
    }

    // Rechercher l'heuristique minimale
    int index = 0;
    for (unsigned int i = 0; i < tmp_score.size(); i++)
    {
        if (tmp_score[i] < minHeuristic)
        {
            minHeuristic = tmp_score[i];
            index = i; // récupération de indice minimale
        }
    }
    new_pos = moves[index];

    compteurMove++;
    return new_pos;
}

std::vector<int> Game::aStarProba(int i, int j, int current_level)
{
    int proba = rand() % (levels.size());
    std::vector<int> new_pos;
    if (proba < current_level)
    {
        new_pos = aStar(i, j);
    }
    else
    {
        new_pos = randMoves(i, j);
    }
    return new_pos;
}

void Game::elimination(std::vector<int> pos_1, std::vector<int> pos_2)
{
    std::vector<int> pos_player = plyr->getPos();
    Board &tmp_board = *levels[pos_player[0]];

    delete tmp_board[pos_1[0]][pos_1[1]];
    delete tmp_board[pos_2[0]][pos_2[1]];
}

/*
void Game::reproduction(std::vector<int> pos_1, std::vector<int> pos_2)
{
    std::vector<int>pos_player = plyr->getPos();
    Board &tmp_board = *levels[pos_player[0]];

    std::vector<int> new_pop = tmp_board.getRandomPoint();
    Streumons *tmp_streums;
    tmp_streums = new Streumons();
    
    tmp_board[new_pop[0]][new_pop[1]] = tmp_streums;
    
}
*/