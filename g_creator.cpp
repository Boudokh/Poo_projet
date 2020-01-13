#include "Game.hpp"
#include <ncurses.h>

// lire un entier saisi au clavier
int read_int();
// lecture et vérification d'un nom de fichier saisi au clavier
std::string read_fname();

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // regex pour vérifier les noms et extensions des fichiers
    std::regex is_board("([a-zA-Z0-9_])+(.board)$");
    std::regex is_game("([a-zA-Z0-9_])+(.game)$");

    if (argc > 1)
    {
        if (argc > 3)
        {
            // au plus deux entrées
            std::cerr << " Too many arguments" << std::endl;
            return 0;
        }
        if (argc == 2 && !std::regex_match(argv[1], is_board))
        {
            std::cerr << "invalid .board file name" << std::endl;
            return 0;
        }
        if (argc == 3)
        {
            if (!std::regex_match(argv[1], is_game))
            {
                std::cerr << "invalid .game file name" << std::endl;
                return 0;
            }
            if (!std::regex_match(argv[2], is_board))
            {
                std::cerr << "invalid .board file name" << std::endl;
                return 0;
            }
            std::ifstream file_check(argv[2]);
            if (!file_check.good())
            {
                std::cerr << "couldn't find .board file" << std::endl;
                return 0;
            }
            file_check.close();

            // créer un '.game' à partir d'un '.board'
            Game *new_game = new Game(argv[2]);
            new_game->save_game(argv[1]);

            std::cout << "jeu \"" << argv[1] << "\" crée avec succées" << std::endl;
            return 0;
        }
    }

    // génération du fichier '.board'
    int hau, lar, nb_level, nb_teupor, nb_diams, nb_streumons, nb_geurchars;

    initscr(); // lacement de la fenetre ncurses

    int i = 0;

    // lecture des attributs utilisés pour la construction des boards
    mvprintw(i, 0, "nb de niveau?\n");
    nb_level = read_int();
    move(i + 1, 0);
    clrtoeol();
    printw("%d", nb_level);

    mvprintw(i += 2, 0, "taille des plateaux? \nhauteur ?\n");
    hau = read_int();
    move(i + 2, 0);
    clrtoeol();
    printw("%d", hau);

    mvprintw(i += 3, 0, "largeur?\n");
    lar = read_int();
    move(i + 1, 0);
    clrtoeol();
    printw("%d", lar);

    mvprintw(i += 2, 0, "nombre de teupors?\n");
    nb_teupor = read_int();
    move(i + 1, 0);
    clrtoeol();
    printw("%d", nb_teupor);

    mvprintw(i += 2, 0, "nb de diams ?\n");
    nb_diams = read_int();
    move(i + 1, 0);
    clrtoeol();
    printw("%d", nb_diams);

    mvprintw(i += 2, 0, "nb de streumons ?\n");
    nb_streumons = read_int();
    move(i + 1, 0);
    clrtoeol();
    printw("%d", nb_streumons);

    mvprintw(i += 2, 0, "nb de geurchars ?\n");
    nb_geurchars = read_int();
    move(i + 1, 0);
    clrtoeol();
    printw("%d", nb_geurchars);

    std::string fname;
    Game *new_game = new Game(hau, lar, nb_level, nb_teupor, nb_diams, nb_streumons, nb_geurchars);

    // demander le nom du fichier '.board' si il n'a pas été saisi en entrée
    if (argc == 1)
    {
        printw("\nSaissez le nom du fichier à sauvegarder (sans extension) \n");
        new_game->save_boards(read_fname() + ".board");
    }
    else if (argc == 2)
    {
        new_game->save_boards(argv[1]);
    }

    endwin();
    return 0;
}

int read_int()
{
    clrtoeol();

    int ch = getch();
    std::regex valid_int("^[1-9][0-9]*$"); // entier naturel > 0
    std::string tmp_int;

    // lecture char par char
    while (ch != '\n')
    {
        tmp_int.push_back(ch);
        ch = getch();
    }

    if (!(std::regex_match(tmp_int, valid_int)))
    {
        printw("Invalid integer");
        return read_int();
    }
    return stoi(tmp_int); // conversion en int
}

std::string read_fname()
{
    clrtoeol();

    std::string fname;
    std::regex valid_file("[a-zA-Z_0-9]*$"); // nom de fichier sans extension

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