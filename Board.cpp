#include "Board.hpp"

Board::Board(std::string txt_board, int _hau, int _lar) : hau(_hau), lar(_lar)
{
    std::vector<Object *> tmp_line;
    Teupor *tmp_teupor;
    Reumus *tmp_reumus;
    Streumons *tmp_streumons;
    Diams *tmp_diams;
    Geurchars *tmp_geurchar;

    for (int i = 0; i < hau; i++)
    {
        for (int j = 0; j < lar; j++)
        {
            switch (txt_board[i * lar + j])
            {
            case 'X':
                tmp_reumus = new Reumus();
                tmp_line.push_back(tmp_reumus);
                break;

            case '-':
                tmp_teupor = new Teupor();
                tmp_line.push_back(tmp_teupor);
                break;

            case '+':
                tmp_teupor = new Teupor();
                tmp_teupor->openTeupor();
                tmp_line.push_back(tmp_teupor);
                break;

            case 's':
                tmp_streumons = new Streumons();
                tmp_line.push_back(tmp_streumons);
                break;

            case '$':
                tmp_diams = new Diams();
                tmp_line.push_back(tmp_diams);
                break;

            case '*':
                tmp_geurchar = new Geurchars();
                tmp_line.push_back(tmp_geurchar);
                break;

            case ' ':
                tmp_line.push_back(NULL);
                break;
            }
        }
        coord.push_back(tmp_line);
        tmp_line.clear();
    }
}

Board::Board(int _hau, int _lar, int nb_teupor, int nb_diams, int nb_streumons, int nb_geurchars) : hau(_hau), lar(_lar)

{
    nb_teupor = std::min(2 * (hau + lar - 2), nb_teupor); //éviter un trop gros nombre de portes
    nb_diams = std::min((lar - 2) * (hau - 2), nb_diams);
    nb_streumons = std::min((lar - 2) * (hau - 2), nb_streumons);
    nb_geurchars = std::min((lar - 2) * (hau - 2), nb_geurchars);

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
    int size_max = 6;
    this->reumus_vert(size_max);
    this->reumus_diag(size_max);
    this->reumus_hor(size_max);

    this->addDiams(nb_diams);
    this->addGeurchars(nb_geurchars);
    this->addStreumons(nb_streumons);

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
    for (std::vector<std::vector<Object *>>::iterator i = coord.begin(); i < coord.end(); i++)
    {
        for (std::vector<Object *>::iterator j = (*i).begin(); j < (*i).end(); j++)
        {
            delete *j;
        }
    }
}

void Board::reumus_vert(int size_max)
{
    int size = (rand() % size_max) + 2;
    std::vector<int> rd_point = getRandomPoint();

    for (int line = rd_point[0]; line < std::min(rd_point[0] + size, hau - 1); line++)
    {
        Reumus *tmp_str = new Reumus();
        coord[line][rd_point[1]] = tmp_str;
    }
}

void Board::reumus_hor(int size_max)
{
    int size = (rand() % size_max) + 2;
    std::vector<int> rd_point = getRandomPoint();

    for (int row = rd_point[1]; row < std::min(rd_point[1] + size, lar - 1); row++)
    {
        Reumus *tmp_str = new Reumus();
        coord[rd_point[0]][row] = tmp_str;
    }
}

void Board::reumus_diag(int size_max)
{
    int size = (rand() % size_max) + 2;
    std::vector<int> rd_point = getRandomPoint();

    for (int i = 0; i < size; i++)
    {
        if (rd_point[0] + i < hau - 1 && rd_point[1] + i < lar - 1)
        {
            Reumus *tmp_str = new Reumus();
            coord[rd_point[0] + i][rd_point[1] + i] = tmp_str;
        }
    }
}

void Board::addDiams(int nb_diams)
{

    // Génération aléatoire diamants.

    while (nb_diams > 0)
    {
        Diams *tmp_diams;
        std::vector<int> rd_point = getRandomPoint();

        if (coord[rd_point[0]][rd_point[1]] == NULL)
        {

            tmp_diams = new Diams();
            coord[rd_point[0]][rd_point[1]] = tmp_diams;
            nb_diams--;
        }
    }
}

void Board::addGeurchars(int nb_geurchars)
{
    // Génération aléatoire geurchars.

    while (nb_geurchars > 0)
    {
        Geurchars *tmp_geurchar;
        std::vector<int> rd_point = getRandomPoint();

        if (coord[rd_point[0]][rd_point[1]] == NULL)
        {
            tmp_geurchar = new Geurchars();
            coord[rd_point[0]][rd_point[1]] = tmp_geurchar;
            nb_geurchars--;
        }
    }
}

void Board::addStreumons(int nb_streumons)
{

    // Génération aléatoire streumons.

    Streumons *tmp_streums;
    while (nb_streumons > 0)
    {
        std::vector<int> rd_point = getRandomPoint();

        if (coord[rd_point[0]][rd_point[1]] == NULL)
        {

            tmp_streums = new Streumons();
            coord[rd_point[0]][rd_point[1]] = tmp_streums;
            nb_streumons--;
        }
    }
}

void Board::placerOueurj(Oueurj *oueurj)
{
    std::vector<int> pos = oueurj->getPos();
    this->coord[pos[1]][pos[2]] = oueurj;
}

void Board::enleverOuerj(Oueurj *oueurj)
{
    std::vector<int> pos = oueurj->getPos();
    this->coord[pos[1]][pos[2]] = NULL;
}

std::vector<int> Board::getRandomPoint()
{
    int point = rand() % ((lar - 2) * (hau - 2));
    std::vector<int> rd_point;
    rd_point.push_back(point / (lar - 2) + 1);
    rd_point.push_back(point % (lar - 2) + 1);
    return rd_point;
}

void Board::openTeupors()
{

    for (int i = 0; i < hau; i++)
    {
        for (int j = 0; j < lar; j++)
        {
            if (j == 0 || j == lar - 1 || i == 0 || i == hau - 1)
            {

                if (coord[i][j]->getSymbol() == '-')
                {
                    dynamic_cast<Teupor *>(coord[i][j])->openTeupor();
                }
            }
        }
    }
}