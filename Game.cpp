#include "Game.hpp"

Game::~Game()
{
    for (std::vector<Board *>::iterator i = levels.begin(); i < levels.end(); i++)
    {
        delete *i;
    }
}

/**
 * @brief  consructeur à partir du nom d'un fichier
 * @param  filename: un nom de fichier .board ou .game
 */
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
            // lecture des dimensi tu tableau
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
                // lecture des détails de la partie (uniquement pour les '.game')
                for (int i = 0; i < 3; i++)
                {
                    getline(ss, token, '*');
                    init_pos.push_back(stoi(token));
                }
                getline(ss, token, '*');
                bool telep_inf = stoi(token);

                getline(ss, token, '*');
                bool nb_telep = stoi(token);

                getline(ss, token, '*');
                int nb_diams = stoi(token);

                getline(ss, token, '*');
                int vies = stoi(token);

                plyr = new Oueurj(init_pos, nb_diams, telep_inf, nb_telep, vies);
            }

            std::string level_string;
            level_string.reserve(this->hau * this->lar);

            // lecture des plateaux
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

    // placement du oueurj pour les '.board'
    if (std::regex_match(filename, is_board))
    {
        init_pos.assign(3, 0);
        plyr = new Oueurj(init_pos);
        placerOueurjRandom();
    }
    else
    {
        this->levels[plyr->getCurrentlevel()]->placer_oueurj(plyr);
    }
}

/**
 * @brief  constructeur à partir de paramétres détaillés
 * @param  _hau: hauteur des plateaux
 * @param  _lar: largeur des plateaux
 * @param  nb_level: nombre de plateaux
 * @param  nb_teupor: nombre de portes par plateau
 * @param  nb_diams: nombre de diams par plateau
 * @param  nb_streumons: nombre de streumon par plateau
 * @param  nb_geurchars: nombre de geurchar par plateau
 */
Game::Game(
    int _hau,
    int _lar,
    int nb_level,
    int nb_teupor,
    int nb_diams,
    int nb_streumons,
    int nb_geurchars)
    : hau(_hau), lar(_lar)
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

/**
 * @brief  replacer le joueur aléatoirement sur le tableau actuel
 * @note   utilisée pour la téléportation aléatoire et le placement initial du joueur
 * @retval None
 */
void Game::placerOueurjRandom()
{
    std::vector<int> rd_point;
    std::vector<int> new_pos = plyr->getPos();
    Board &tmp_board = *levels[new_pos[0]];
    bool keep_search = true;

    // calcule une position aléatoire sur le tableau et vérifie qu'elle n'est pas déjà occupée
    while (keep_search)
    {
        rd_point = this->levels[new_pos[0]]->getRandomPoint();
        new_pos[1] = rd_point[0], new_pos[2] = rd_point[1];

        if (tmp_board[new_pos[1]][new_pos[2]] == NULL)
            keep_search = false;
    }

    plyr->setPos(new_pos);
    this->levels[new_pos[0]]->placer_oueurj(plyr);
}

/**
 * @brief  génére le tableau du niveau actuel sous format string avec l'affichage du score
 * @note   utilisée dans l'affichage ncurses dans le game player
 * @retval string résumant l'état actuel du jeu
 */
std::string Game::toString() const
{
    std::stringstream level_strm = this->levels[plyr->getCurrentlevel()]->toStream(true);
    std::stringstream plyr_info = plyr->toStream(this->levels.size());

    std::string tmp_str, sortie = "";

    for (int i = 0; i < hau; i++)
    {
        if (level_strm)
        {
            getline(level_strm, tmp_str);
            sortie += tmp_str;
            tmp_str.clear();

            if (plyr_info)
            {
                getline(plyr_info, tmp_str);
                sortie += tmp_str;
            }

            sortie += "\n";
        }
    }

    return sortie;
}

/**
 * @brief  sauvegarde le jeu actuel dans un fichier .game
 * @note   contient une ligne de description de l'état du (position du Oueurj, quantité de diams, téléportations, etc)
 *         et tous lea tableaux du jeu
 * @param  filename: nom du fichier de destination (avec extension .game)
 * @retval None
 */
void Game::save_game(std::string filename)
{
    std::ofstream fichier_game;
    fichier_game.open(filename);

    //premiére ligne du fichier contentenant les données de la partie séparés par '*'
    char sep = '*';
    fichier_game << this->hau << sep << this->lar << sep << this->levels.size() << sep;

    std::vector<int> plyr_pos = plyr->getPos();
    for (unsigned int i = 0; i < plyr_pos.size(); i++)
    {
        fichier_game << plyr_pos[i] << sep;
    }
    fichier_game << plyr->getTelep(true) << sep << plyr->getNbDiams() << sep << plyr->getVies() << sep << std::endl;

    //écriture des plateaux séparés par '#'
    for (std::vector<Board *>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        fichier_game << (*it)->toString(true) << '#' << std::endl;
    }

    fichier_game.close();
}

/**
 * @brief  sauvegarde uniquement les plateaux du jeu actuel dans un fichier .board
 * @note   
 * @param  filename: nom du fichier de destination (avec extension .board)
 * @retval None
 */
void Game::save_boards(std::string filename)
{
    std::ofstream fichier_board;
    fichier_board.open(filename);

    char sep = '*';
    fichier_board << this->hau << sep << this->lar << sep << this->levels.size() << sep << std::endl;

    //écriture des plateaux séparés par '#'
    for (std::vector<Board *>::iterator it = this->levels.begin(); it != this->levels.end(); ++it)
    {
        fichier_board << (*it)->toString(false) << '#' << std::endl;
    }
    fichier_board.close();
}

/**
 * @brief  execution d'un tour de jeu
 * @note   un mouvement du joueur suivi des mouvements de streumons
 * @param  move: direction du déplacement
 * @retval l'état du jeu : 0 = en cours, 1 = victoire, -1 = défaite
 */
int Game::play_round(const char move)
{
    if (plyr->getState() == 0)
    {
        move_oueurj(move);
        play_streumons();
    }

    return plyr->getState();
}

/**
 * @brief  déplacement du Oueurj
 * @note
 * @param  move: direction du déplacement : "azedcxwq" autorisés, "t" pour les téléportations
 * @retval none
 */
void Game::move_oueurj(char move)
{

    std::vector<int> old_pos = plyr->getPos();
    std::vector<int> new_pos = old_pos;

    // calcul de la nouvelle position
    switch (move)
    {
    case 'z': // haut
        new_pos[1] = std::max(0, old_pos[1] - 1);
        break;
    case 'x': // bas
        new_pos[1] = std::min(hau - 1, old_pos[1] + 1);
        break;
    case 'q': // gauche
        new_pos[2] = std::max(0, old_pos[2] - 1);
        break;
    case 'd': // droite
        new_pos[2] = std::min(lar - 1, old_pos[2] + 1);
        break;
    case 'a': // haut + gauche
        new_pos[1] = std::max(0, old_pos[1] - 1);
        new_pos[2] = std::max(0, old_pos[2] - 1);
        break;
    case 'e': // haut + droite
        new_pos[1] = std::max(0, old_pos[1] - 1);
        new_pos[2] = std::min(lar - 1, old_pos[2] + 1);
        break;
    case 'c': // bas + droite
        new_pos[1] = std::min(hau - 1, old_pos[1] + 1);
        new_pos[2] = std::min(lar - 1, old_pos[2] + 1);
        break;
    case 'w': // bas + gauche
        new_pos[1] = std::min(hau - 1, old_pos[1] + 1);
        new_pos[2] = std::max(0, old_pos[2] - 1);
        break;
    case 't': // téléportation : Oueurj rplacé aléatoirement dans le même plateau
        if (plyr->teleport())
        {
            this->levels[old_pos[0]]->enlever_oueurj(plyr);
            plyr->setPos(new_pos);
            placerOueurjRandom();
        }
        return;
    }

    // plateau actuel
    Board &tmp_board = *levels[old_pos[0]];

    //vérifie que la nouvelle case est non vide (NULL)
    if (tmp_board[new_pos[1]][new_pos[2]])
    {
        char tmp_sym = tmp_board[new_pos[1]][new_pos[2]]->getSymbol();
        if (tmp_sym == 's')
        {
            // mort lors de la rencontre avec un streumon
            plyr->die();
            return;
        }
        else if (tmp_sym == 'X' || tmp_sym == '-')
        {
            // ne rien faire si c'est un mur ou une teupor fermée
        }
        else if (tmp_sym == '+')
        {
            // passage au niveau supérieur
            this->levels[old_pos[0]]->enlever_oueurj(plyr);
            if (old_pos[0] < (int)levels.size() - 1)
            {
                plyr->levelUp();
                placerOueurjRandom();
            }
            else
            {
                // victoire si c'est le dernier niveau
                plyr->win();
                placerOueurjRandom();
                return;
            }
        }
        else
        {
            if (tmp_sym == '$')
            {
                // ouvre une porte aléatoire
                delete (tmp_board[new_pos[1]][new_pos[2]]);
                plyr->eatDiams();
                levels[old_pos[0]]->open_teupors();
            }

            if (tmp_sym == '*')
            {
                // déclenche les téléportations infinies
                delete (tmp_board[new_pos[1]][new_pos[2]]);
                plyr->switch_teleport();
            }

            // replacement du Oueurj
            this->levels[old_pos[0]]->enlever_oueurj(plyr);
            plyr->setPos(new_pos);
            this->levels[old_pos[0]]->placer_oueurj(plyr);
        }
    }
    else
    {
        // déplacement simple si la case est vide
        this->levels[old_pos[0]]->enlever_oueurj(plyr);
        plyr->setPos(new_pos);
        this->levels[old_pos[0]]->placer_oueurj(plyr);
    }
    return;
}

/**
 * @brief  déplacements des streumons
 * @retval None
 */
void Game::play_streumons()
{
    std::vector<int> plyr_p = plyr->getPos();
    Board &curr_board = *levels[plyr_p[0]];

    std::vector<int> new_pos, old_pos;
    std::string symb_list = curr_board.toString(false);

    for (int i = 0; i < hau; i++)
    {
        for (int j = 0; j < lar; j++)
        {
            // recherche des streumons
            if (symb_list[i * (lar + 1) + j] == 's')
            {
                // choix de l'algorithme
                switch (dynamic_cast<Streumons *>(curr_board[i][j])->getType())
                {
                case 0:
                    new_pos = rand_moves(i, j);
                    break;
                case 1:
                    new_pos = a_star(i, j);
                    break;
                case 2:
                    new_pos = a_star_proba(i, j, plyr_p[0]);
                    break;
                default:
                    break;
                }

                old_pos = {i, j};
                curr_board.moveStrm(old_pos, new_pos);
                if (new_pos[0] == plyr_p[1] && new_pos[1] == plyr_p[2])
                {
                    this->plyr->die();
                    this->placerOueurjRandom();
                }
                if (symb_list[new_pos[0] * (lar + 1) + new_pos[1]] == 's')
                {
                    // choix du le gestion des interactions des streumons
                    switch (dynamic_cast<Streumons *>(curr_board[new_pos[0]][new_pos[1]])->getTypeEvol())
                    {
                    case 0:
                        curr_board.elimination(old_pos, new_pos);
                        break;
                    case 1:
                        curr_board.reproduction(old_pos, new_pos);
                    case 2:
                        curr_board.fusion(old_pos, new_pos);
                    default:
                        break;
                    }
                }
            }
        }
    }
}

/**
 * @brief  mouvement autorisés pour le streumon parmi les case voisines
 * @param  i: ligne du streumon
 * @param  j: colonne
 * @retval liste des mouvements autorisés
 */
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
                // si le oueurj est dans une case voisine, retourner uniquement ce mouvement
                tmp_move = {x, y};
                legal_moves.push_back(tmp_move);
            }
        }
    }

    return legal_moves;
}

/**
 * @brief  déplacement aléatoire du streumon
 * @param  i: ligne du streumon
 * @param  j: colonne
 * @retval std::vector<int> case choisie aléatoirement
 */
std::vector<int> Game::rand_moves(int i, int j)
{
    std::vector<int> plyr_p = plyr->getPos();
    std::vector<int> old_pos{i, j};

    std::vector<std::vector<int>> legal_moves = legalMoves(i, j);

    return legal_moves[rand() % legal_moves.size()];
}

/**
 * @brief  algorithme A* pour les déplacement des streuemons
 * @param  i: ligne du streumon
 * @param  j: colonne
 * @retval std::vector<int> case de destination
 */
std::vector<int> Game::a_star(int i, int j)
{
    std::vector<std::vector<int>> moves = legalMoves(i, j);

    // heuristique (distance euclidienne) pour les cases choisies (valides) à la destination finale.
    std::vector<double> tmp_score;
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
            index = i;
        }
    }
    new_pos = moves[index];

    compteurMove++;
    return new_pos;
}

/**
 * @brief  choix entre mouvelent aléatoire ou A*
 * @note   difficulté qui augmente: probablité de A* augment au fil des niveau
 * @param  i: ligne du streumon
 * @param  j: colonne
 * @param  current_level: le niveau actuel
 * @retval std::vector<int> case de destination
 */
std::vector<int> Game::a_star_proba(int i, int j, int current_level)
{
    int proba = rand() % (levels.size());
    std::vector<int> new_pos;
    if (proba < current_level)
    {
        new_pos = a_star(i, j);
    }
    else
    {
        new_pos = rand_moves(i, j);
    }
    return new_pos;
}
