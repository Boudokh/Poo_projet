#include "Game.hpp"
#include "Board.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    srand(time(NULL));


    Board *test = new Board(30, 30, 200);

    int lar = 30;
    int hau = 30;

    
    int reumus = rand() % (((lar-2))*(hau-2));
    int reumus_1 = rand() % (((lar-2)*(hau-2)));

    
    /*Reumus *reumsInt = new Reumus();
    test->coord[(reumus/lar)+2][(reumus%lar)-1] = reumsInt;

    
    for (int k = (reumus/lar)+2; k < ((reumus/lar)+2)+6; k++)
    {
        Reumus *reumsIntSucc = new Reumus();
        test->coord[k+1][(reumus%lar)-1] = reumsIntSucc;
    }
    */

    int d = rand() % 6;
    std::cout << d << std::endl;
    for (int v = (reumus/lar)+2; v < ((reumus/lar)+2)+d; v++)
    {
        Reumus *reumsIntSucc1 = new Reumus();
        test->coord[v+1][(reumus%lar)-1] = reumsIntSucc1;

        for (int k = ((reumus%lar)-1)+1 ; k <= 6 - ((reumus/lar)+2)+d; k++)
        {
            Reumus *reumsIntSucc2 = new Reumus();
            test->coord[((reumus/lar)+2)+d][k] = reumsIntSucc2;
        }
    }

    for (int v = (reumus_1/lar)+2; v < ((reumus_1/lar)+2)+d; v++)
    {
        Reumus *reumsIntSucc3 = new Reumus();
        test->coord[v+1][(reumus_1%lar)-1] = reumsIntSucc3;

        for (int k = ((reumus_1%lar)-1)+1 ; k <= 6 - ((reumus_1/lar)+2)+d; k++)
        {
            Reumus *reumsIntSucc4 = new Reumus();
            test->coord[((reumus_1/lar)+2)+d][k] = reumsIntSucc4;
        }
    }
    /*
    // Stremons

    int streum = rand() % ((lar-2)*(hau-2));
    Streumons *streumInt = new Streumons();
    if(test->coord[(streum/lar)+2][(streum%lar)-1]!=NULL)
    {
        test->coord[(streum/lar)+2][((streum%lar)-1)+1] = streumInt;
    }
    test->coord[(streum/lar)+2][(streum%lar)-1] = streumInt;
    
    */

    std::cout << "/" << reumus/lar << " %" << reumus%lar << std::endl;

    std::cout << test->display() << std::endl;

    Game a(30, 30, 10, 6);
    //a.affiche();
    //a.to_txt();
    a.from_text();
    return 0;

 }
