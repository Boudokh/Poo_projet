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

    std::regex is_board("([a-zA-Z0-9_])+(.board)$");
    std::regex is_game("([a-zA-Z0-9_])+(.game)$");

    this->compteurMove = 0;

    if (std::regex_match(filename, is_board) || std::regex_match(filename, is_game))
    {
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

            if (std::regex_match(filename, is_game))
            {
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

    if (std::regex_match(filename, is_board))
    {
        init_pos.assign(3, 0);
        plyr = new Oueurj(init_pos);
        placerOueurjRandom();
    }
    else{
        this->levels[plyr->getCurrentlevel()]->placerOueurj(plyr);
    }
}

Game::Game()
{
    int nb_level, nb_teupor, nb_diams, nb_streumons, nb_geurchars;
    this->compteurMove = 0;

    std::cout << "nb de niveau?" << std::endl;
    nb_level = get_valid_int();
    std::cout << "taille des plateaux? \nhauteur ?" << std::endl;
    this->hau = get_valid_int();
    std::cout << "largeur?" << std::endl;
    this->lar = get_valid_int();
    std::cout << "nombre de teupors?";
    nb_teupor = get_valid_int();
    std::cout << "nb de diams ?" << std::endl;
    nb_diams = get_valid_int();
    std::cout << "nb de streumons ?" << std::endl;
    nb_streumons = get_valid_int();
    std::cout << "nb de geurchars ?" << std::endl;
    nb_geurchars = get_valid_int();

    for (int i = 0; i < nb_level; i++)
    {
        this->levels.push_back(new Board(this->hau, this->lar, nb_teupor, nb_diams, nb_streumons, nb_geurchars));
    }

    std::vector<int> init_pos;
    init_pos.assign(3, 0);
    plyr = new Oueurj(init_pos);
    placerOueurjRandom();
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
        std::cout << (*it)->toString(false) << std::endl;
    }
}

void Game::dispCurrLevel() const
{
    std::stringstream level_strm = this->levels[plyr->getCurrentlevel()]->toStream(true);
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

std::string Game::toString() const
{
    std::stringstream level_strm = this->levels[plyr->getCurrentlevel()]->toStream(true);
    std::stringstream plyr_info = plyr->toStream();

    std::string tmp_str, sortie = "";

    for (int i = 0; i < hau; i++)
    {
        getline(level_strm, tmp_str);
        sortie += tmp_str;
        tmp_str.clear();
        getline(plyr_info, tmp_str);
        sortie += tmp_str;
        if (i == 2)
        {
            sortie += "/" + std::to_string(this->levels.size());
        }
        sortie += "\n";
    }

    return sortie;
}

void Game::save_game(std::string filename)
{
    std::ofstream fichier_game;
    fichier_game.open(filename);

    char sep = '*';
    fichier_game << this->hau << sep << this->lar << sep << this->levels.size() << sep;
    std::vector<int> plyr_pos = plyr->getPos();

    for (unsigned int i = 0; i < plyr_pos.size(); i++)
    {
        fichier_game << plyr_pos[i] << sep;
    }
    fichier_game << plyr->getTelep() << sep << plyr->getNbDiams() << sep << std::endl;

    for (std::vector<Board *>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        fichier_game << (*it)->toString(false) << '#' << std::endl;
    }

    fichier_game.close();
}

void Game::save_boards(std::string filename)
{
    std::ofstream fichier_board;
    fichier_board.open(filename);

    char sep = '*';
    fichier_board << this->hau << sep << this->lar << sep << this->levels.size() << sep << std::endl;

    for (std::vector<Board *>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        fichier_board << (*it)->toString(false) << '#' << std::endl;
    }
    fichier_board.close();
}

int Game::play_round(char move)
{
    if (plyr->getState() == 0)
    {
        moveOueurj(move);
        playStreumons();
    }

    return plyr->getState();
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
            return true;
        }
        if (tmp_sym == 'X' || tmp_sym == '-')
        {
            //std::cout << "impossible" << std::endl;
        }
        else if (tmp_sym == '+')
        {
            this->levels[old_pos[0]]->enleverOuerj(plyr);
            if (old_pos[0] < (int)levels.size() - 1)
            {
                plyr->levelUp();
                //std::cout << "levelup" << plyr->getPos()[0] << " " << plyr->getPos()[1] << " " << plyr->getPos()[2] << std::endl;
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
            this->levels[old_pos[0]]->placerOueurj(plyr);
        }
    }
    else
    {
        this->levels[old_pos[0]]->enleverOuerj(plyr);
        plyr->setPos(new_pos);
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
    //auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> plyr_p = plyr->getPos();
    Board &curr_board = *levels[plyr_p[0]];

    std::vector<int> new_pos, old_pos;
    std::string symb_list = curr_board.toString(false);

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
                //std::cout << "types evol : " << dynamic_cast<Streumons *>(curr_board[new_pos[0]][new_pos[1]])->getTypeEvol() << std::endl;
                if (new_pos[0] == plyr_p[1] && new_pos[1] == plyr_p[2])
                {
                    this->plyr->die();
                }
                if (symb_list[new_pos[0] * (lar + 1) + new_pos[1]] == 's')
                {
                    switch (dynamic_cast<Streumons *>(curr_board[new_pos[0]][new_pos[1]])->getTypeEvol())
                    {
                    case 0:
                        //std::cout << "Streumons has been slain" << std::endl;
                        curr_board.elimination(old_pos, new_pos);
                        break;
                    case 1:
                        //std::cout << "Un streums est apparu !" << std::endl;
                        curr_board.reproduction(old_pos, new_pos);
                    case 2:
                        //std::cout << "Un bonus est apparu, thanks les streums !" << std::endl;
                        curr_board.fusion(old_pos, new_pos);
                    default:
                        break;
                    }
                }
            }
        }
    }
    /*
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    */
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

int Game::get_valid_int()
{
    int input;

    while (!(std::cin >> input))
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "saissez un entier valide" << std::endl;
    }
    return input;
}
