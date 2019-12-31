#include "Game.hpp"
#include <regex>
#include <ncurses.h>
#include <dirent.h>

char getMove();

int main(int argc, char *argv[])
{
    Game *new_game = new Game(15, 30, 5, 6, 3, 2, 2);

    std::regex is_board("([a-zA-Z0-9_])+(.cpp)$");

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

    initscr();
    int i = 0;
    for (std::vector<std::string>::iterator it = file_list.begin(); it != file_list.end(); it++, i++)
    {
        mvprintw(i, 0, "%2d. %s", i + 1, it->c_str());
    }
    getch();
    char next_move = '0';
    int game_state = 0;

    while (next_move != 's' && game_state == 0)
    {
        clear();
        printw(new_game->toString().c_str());
        next_move = getMove();
        game_state = new_game->play_round(next_move);
    }

    if (game_state == 1)
    {
        printw("VICTOIRE");
    }
    else if (game_state == -1)
    {
        printw("DEFAITE");
    }

    getch();
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