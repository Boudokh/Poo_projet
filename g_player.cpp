#include "Game.hpp"
#include <regex>
#include <ncurses.h>
#include <dirent.h>

char getMove();
std::vector<std::string> read_file_names();

int main(int argc, char *argv[])
{

    std::vector<std::string> file_list = read_file_names();
    bool replay = true;
    initscr();
    do
    {
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
            mvprintw(i + 1, 0, " %2d. %s", i + 1, it->c_str());
        }
        move(1, 0);
        keypad(stdscr, true);

        int input, x, y;

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

        Game *new_game = new Game(file_list[y - 1]);

        char next_move = '0';
        int game_state = 0;

        while (next_move != 's' && game_state == 0)
        {
            clear();
            printw(new_game->toString().c_str());
            next_move = getMove();
            game_state = new_game->play_round(next_move);
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
        getyx(stdscr, y, x);
        printw("\nAppuyez sur n'importe quelle touche pour continuer");
        getch();
        clear();
        mvprintw(0, 0, "Voulez vous rejouer?\n 1. oui\n 2. non ");
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
                move(std::min(2, y + 1), 0);
                break;
            default:
                break;
            }
        } while (input != 10);

        getyx(stdscr, y, x);

        if (y == 2)
        {
            replay = false;
        }

    } while (replay);
    endwin();

    return 0;
}

char getMove()
{
    int key;
    std::string legal_moves = "azeqsdwxct";
    do
    {
        key = getch();
        clrtoeol();
    } while (legal_moves.find(key) == std::string::npos);

    return key;
}

std::vector<std::string> read_file_names()
{

    std::regex is_board("([a-zA-Z0-9_])+(.board)$");

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
                //std::cout << tmp_fname << std::endl;
            }
        }
        closedir(d);
    }

    return file_list;
}