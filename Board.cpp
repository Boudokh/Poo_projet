#include "Board.hpp"

Board::Board(int _hau, int _lar, int nb_teupor, int nb_diams, int nb_streumons, int nb_geurchars) : hau(_hau), lar(_lar)
{
    nb_teupor = std::min(2 * (hau + lar - 2), nb_teupor); //éviter un trop gros nombre de portes
    nb_diams = std::min((lar-2)*(hau-2), nb_diams); 
    nb_streumons = std::min((lar-2)*(hau-2), nb_streumons);
    nb_geurchars = std::min((lar-2)*(hau-2), nb_geurchars);

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

void Board::reumus_vert(int _lar, int _hau, int size_max, int reumus)
{
    int size = (rand() % size_max) + 2;
    int x_start = reumus/ (lar -2) +1;
    int y_start = reumus % (lar - 2) +1;
    for (int line = x_start; line < std::min(x_start + size, hau - 1); line++)
    {
        Reumus *tmp_str = new Reumus();
        coord[line][y_start] = tmp_str;
    }
}

void Board::reumus_hor(int _lar, int _hau, int size_max, int reumus)
{
    int size = (rand() % size_max) + 2;
    int x_start = reumus / lar + 1;
    int y_start = reumus % lar + 1;

    for (int row = y_start; row < std::min(y_start + size, lar - 1); row++)
    {
        Reumus *tmp_str = new Reumus();
        coord[x_start][row] = tmp_str;
    }
}

void Board::reumus_diag(int _lar, int _hau, int size_max, int reumus)
{
    int size = (rand() % size_max) + 2;
    int x_start = reumus / lar + 1;
    int y_start = reumus % lar + 1;

     for (int i = 0; i < size; i++)
    {
        if (x_start + i < hau - 1 && y_start + i< lar - 1)
        {
            Reumus *tmp_str = new Reumus();
            coord[x_start + i][y_start + i] = tmp_str;
        }
    }

}

void Board::diams_interieur(int _lar, int _hau, int nb_diams)
{

    // Génération aléatoire diamants.

    while(nb_diams>0)
    {
        Diams *tmp_diams;
        int gen_diams = rand() % ((lar-2)*(hau-2));
        int coord_i = gen_diams/(lar-2)+1;
        int coord_j = gen_diams%(lar-2)+1;

        if (coord[coord_i][coord_j] == NULL)
        {
            
            tmp_diams = new Diams();
            coord[coord_i][coord_j] = tmp_diams;
            nb_diams--;
        }
    }
}

void Board::geurchars_interieur(int _lar, int _hau, int nb_geurchars)
{
    // Génération aléatoire geurchars.

    while(nb_geurchars>0)
    {
        Geurchars *tmp_geurchar ;
        int gen_geurchar = rand() % ((lar-2)*(hau-2));
        int x_abs = gen_geurchar/(lar-2)+1;
        int y_ord = gen_geurchar%(lar-2)+1;

        if(coord[x_abs][y_ord] == NULL)
        {
            tmp_geurchar = new Geurchars();
            coord[x_abs][y_ord] = tmp_geurchar;
            nb_geurchars--;
        }
    }

}

void Board::streums_interieur(int _lar, int _hau, int nb_streumons)
{
      

    // Génération aléatoire streumons.

    Streumons *tmp_streums;
    while(nb_streumons>0)
    {
        int gen_streums = rand() % ((lar-2)*(hau-2));
        int abs_i = gen_streums/(lar-2)+1;
        int abs_j = gen_streums%(lar-2)+1;

        if (coord[abs_i][abs_j] == NULL)
        {
            
            tmp_streums = new Streumons();
            coord[abs_i][abs_j] = tmp_streums;
            nb_streumons--;
        }
    }
}


