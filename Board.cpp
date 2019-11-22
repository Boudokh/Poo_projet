#include "Board.hpp"

Board::Board(int x, int y, int nb_teupor) : lar(x), lon(y)
{
    srand(time(NULL));

    std::vector<Object *> tmp_line;

    for (int i = 0; i < lar; i++)
    {
        for (int j = 0; j < lon; j++)
        {

            if (j == 0 || j == lon - 1 || i == 0 || i == lar - 1)
            {
                Reumus *tmp_reumus = new Reumus();
                tmp_line.push_back(tmp_reumus);
            }
            else
            {
                Object *tmp_obj = NULL;
                tmp_line.push_back(tmp_obj);
            }
        }
        coord.push_back(tmp_line);
        tmp_line.clear();
    }

    while (nb_teupor > 0)
    {
        nb_teupor--;
        int coord_i, coord_j;
        int rd = rand() % (2 * (lon + lar - 2));

        if (rd <= lar - 1)
        {
            std::cout << "1" << std::endl;
            coord_i = 0;
            coord_j = rd;
        }
        else if (rd <= lon + lar - 1)
        {
            std::cout << "2" << std::endl;
            coord_i = rd - lar - 1;
            coord_j = lar -1;
        }
        else if (rd <= 2 * lar + lon - 1)
        {
            std::cout << "3" << std::endl;
            coord_i = lon - 1;
            coord_j = rd - lon - lar - 2;
        }
        else
        {
            std::cout << "4 " << rd << std::endl;
            coord_i = rd - 2* lar - lon  + 3;
            coord_j = 0;
        }
        Teupor* tmp_teupor = new Teupor();
        std::cout << coord_i << " " << coord_j << std::endl;
        coord[coord_i][coord_j] = tmp_teupor;
    }
}

std::string Board::display()
{
    std::string plateau = "";
    for (int i = 0; i < lar; i++)
    {
        for (int j = 0; j < lon; j++)
        {
            if (coord[i][j])
            {
                plateau.push_back(coord[i][j]->getSymbol());
                //std::cout << *(coord[i][j]->getSymbol());
            }
            else
            {
                plateau += " ";
            }
        }
        plateau += "\n";
    }

    return plateau;
}