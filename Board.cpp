#include "Board.hpp"

Board::Board(int x, int y, int nb_teupor) : lar(x), lon(y)
{
    srand(time(NULL));

    nb_teupor = std::min(2*(lon + lar - 2), nb_teupor); //éviter un trop gros nombre de portes

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
    std::cout << nb_teupor << std::endl;
    while (nb_teupor > 0)
    {
        int coord_i, coord_j;
        int rd = rand() % (2 * (lon + lar));
        if (rd < lar)
        {
            coord_i = 0;
            coord_j = rd;
        }
        else if (rd < lon + lar)
        {
            coord_i = rd - lar;
            coord_j = lar - 1;
        }
        else if (rd < 2 * lar + lon)
        {
            coord_i = lon - 1;
            coord_j = rd - lon - lar;
        }
        else
        {
            coord_i = rd - 2 * lar - lon;
            coord_j = 0;
        }

        if (coord[coord_i][coord_j]->getName() == typeid(Reumus *).name())
        {
            Teupor *tmp_teupor = new Teupor();
            coord[coord_i][coord_j] = tmp_teupor;
            nb_teupor--;
            std::cout << nb_teupor << std::endl;

        }
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