#include "Game.hpp"
#include <ncurses.h>
#include <dirent.h>

// récuperer un char qui creespond à un mouvement
char getMove();
// lire les noms de fichiers .game dans le dossier courant
std::vector<std::string> read_file_names();
// lire un nom de fichier saisi au clavier
std::string read_fname();
// demander un réponse oui ou non à l'utilisateur
bool yes_no(WINDOW *stdscr);

int main(int argc, char *argv[])
{
    srand(time(NULL));

    std::vector<std::string> file_list;
    bool replay = true;
    int input, x, y;

    Game *my_game;

    std::regex is_game("([a-zA-Z0-9_])+(.game)$");

    if (argc > 2)
    {
        std::cerr << " Too many arguments" << std::endl;
        return 0;
    }
    else if (argc == 2)
    {
        // vérifier si l'utilisateur a saisi un fichier .game et le lire
        if (!regex_match(argv[1], is_game))
        {
            std::cerr << "invalid .game file name" << std::endl;
            return 0;
        }
        std::ifstream file_check(argv[1]);
        if (!file_check.good())
        {
            std::cerr << "couldn't find .game file" << std::endl;
            return 0;
        }
        file_check.close();
    }

    initscr();
    do
    {
        keypad(stdscr, true);

        // proposer la liste des fichiers .game dans le dossier courant et laisser l'utilisateur choisir grâce aux fléches haut et bas
        if (argc == 1)
        {
            file_list = read_file_names();
            int i = 0;
            if (file_list.size() == 0)
            {
                mvprintw(0, 0, "Aucun fichier .board détécté, veuillez en créer grace au fichier \'gc\'\nAppuyez sur n'importe quelle touche pour sortir");
                getch();
                endwin();
                return 0;
            }
            mvprintw(0, 0, "choisissez le fichier board à jouer: ");
            for (std::vector<std::string>::iterator it = file_list.begin(); it != file_list.end(); it++, i++)
            {
                mvprintw(i + 1, 0, "  %s", it->c_str());
            }
            move(1, 0);

            do
            {
                input = getch();
                getyx(stdscr, y, x);
                switch (input)
                {
                case KEY_UP:
                    move(std::max(1, y - 1), 0);
                    break;
                case KEY_DOWN:
                    move(std::min(int(file_list.size()), y + 1), 0);
                    break;
                default:
                    break;
                }
            } while (input != 10);

            getyx(stdscr, y, x);

            my_game = new Game(file_list[y - 1]);
        }
        else
        {
            my_game = new Game(argv[1]);
        }

        char next_move = '0';
        int game_state = 0;

        while (next_move != 'o' && game_state == 0)
        {
            clear();
            printw(my_game->toString().c_str());
            next_move = getMove();
            game_state = my_game->play_round(next_move);
        }

        getyx(stdscr, y, x);

        if (game_state == 1)
        {
            mvprintw(y, 0, "\nVICTOIRE");
        }
        else if (game_state == -1)
        {
            mvprintw(y, 0, "\nDEFAITE");
        }
        else if (game_state == 0)
        {
            mvprintw(y, 0, "Partie non ternminée, voulez vous sauvegarder?");
            move(y + 1, 0);

            if (yes_no(stdscr))
            {
                printw("\nSaissez le nom du fichier à sauvegarder (sans l'extension .game) \n");
                my_game->save_game(read_fname() + ".game");
            }
        }
        getyx(stdscr, y, x);
        printw("\nAppuyez sur n'importe quelle touche pour continuer");
        getch();
        clear();

        mvprintw(0, 0, "Voulez vous rejouer?\n");
        replay = yes_no(stdscr);

    } while (replay);
    endwin();

    return 0;
}

bool yes_no(WINDOW *stdscr)
{
    int input, y, x;
    getyx(stdscr, y, x);
    mvprintw(y, 0, " 1. oui\n 2. non ");
    move(y, 0);
    int yes = y;
    do
    {
        input = getch();
        getyx(stdscr, y, x);
        switch (input)
        {
        case KEY_UP:
            move(std::max(yes, y - 1), 0);
            break;
        case KEY_DOWN:
            move(std::min(yes + 1, y + 1), 0);
            break;
        default:
            break;
        }
    } while (input != 10);

    getyx(stdscr, y, x);

    if (y == yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char getMove()
{
    int key;
    std::string legal_moves = "azeqodwxct";
    do
    {
        key = getch();
        clrtoeol();
    } while (legal_moves.find(key) == std::string::npos);

    return key;
}

std::vector<std::string> read_file_names()
{
    std::regex is_board("([a-zA-Z0-9_])+(.game)$");

    std::string tmp_fname;
    struct dirent *dir;

    std::vector<std::string> file_list;

    DIR *d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            tmp_fname = dir->d_name;
            if (std::regex_match(tmp_fname, is_board))
            {
                file_list.push_back(tmp_fname);
            }
        }
        closedir(d);
    }

    return file_list;
}

std::string read_fname()
{
    clrtoeol();

    std::string fname;
    std::regex valid_file("[a-zA-Z_][a-zA-Z_0-9]*$");

    int ch = getch();

    while (ch != '\n')
    {
        fname.push_back(ch);
        ch = getch();
    }

    if (!(std::regex_match(fname, valid_file)))
    {
        printw("Invalid file name");
        return read_fname();
    }
    return fname;
}