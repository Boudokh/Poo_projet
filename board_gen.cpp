#include "Game.hpp"
#include "Board.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    Board *test = new Board(8, 10, 200);
    std::cout << test->display() << std::endl;

    Game a(6, 12, 10, 6);
    //a.affiche();
    //a.to_txt();
    a.from_text();
    return 0;

    int lar = 30;
    int hau = 20;

    int reumus = rand() % ((lar-2)*(hau-2));
    int coord_reums_x, coord_reums_y;
    coord_reums_y =  reumus/hau;
    coord_reums_x = reumus%hau;

    //int c = rand() % 3;
    int c = 0;

    switch (c)
    {
    case '0' : // cas mur verticale 
        for (int i = coord_reums_x; i<= coord_reums_x+lar; i++)
        {
            Reumus *reumsInt = new Reumus();
            test->coord[coord_reums_x][coord_reums_y] = reumsInt;
        }
        break;
        
    /*
        case '1' : // cas mur horizontale
        for (int   j<= coord_reums_y+len; j++)
        {
            Reumus *reumsInt = new Reumus();
            coord[coord_reums_x][coord_reums_y] = reumsInt;
        }
        break;
    case '2' : // cas mur courbé manière 1 ( vers le bas )
        int d = rand() % (2*len) - len;
        for (int v = coord_reums_x; v<= ((coord_reums_x+d + coord_reums_x+(len-d))); v++)
        {
            Reumus *reumsInt = new Reumus();
            tmp.line.push_back(reumsInt);
        }
        break;
    */

    default:
        break;
    }

}