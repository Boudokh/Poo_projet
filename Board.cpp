#include "Board.hpp"

Board::Board(int _hau, int _lar, int nb_teupor) : hau(_hau), lar(_lar)
{
    nb_teupor = std::min(2 * (hau + lar - 2), nb_teupor); //éviter un trop gros nombre de portes

    std::vector<Object *> tmp_line;
    for (int i = 0; i < hau; i++)
    {
        for (int j = 0; j < lar; j++)
        {

            if (j == 0 || j == lar - 1 || i == 0 || i == hau - 1)
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
        int coord_i, coord_j;
        int rd = rand() % (2 * (hau + lar));
        if (rd < lar)
        {
            coord_i = 0;
            coord_j = rd;
        }
        else if (rd < hau + lar)
        {
            coord_i = rd - lar;
            coord_j = lar - 1;
        }
        else if (rd < 2 * lar + hau)
        {
            coord_i = hau - 1;
            coord_j = rd - hau - lar;
        }
        else
        {
            coord_i = rd - 2 * lar - hau;
            coord_j = 0;
        }
        if (coord[coord_i][coord_j]->getName() == typeid(Reumus *).name())
        {
            Teupor *tmp_teupor = new Teupor();
            coord[coord_i][coord_j] = tmp_teupor;
            nb_teupor--;
        }
    }

    //dynamic_cast<Teupor *>(coord[8][0])->openTeupor();
}

std::string Board::display()
{
    std::string plateau = "";
    for (int i = 0; i < hau; i++)
    {
        for (int j = 0; j < lar; j++)
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

Board::~Board()
{
    for(std::vector<std::vector<Object*>>::iterator i = coord.begin(); i<coord.end();i++)
    {
        for(std::vector<Object *>::iterator j = (*i).begin(); j<(*i).end(); j++ )
        {
            delete *j;
        }
    }
}


