#include "Board.hpp"

Board::Board(std::string txt_board, int _hau, int _lar) : hau(_hau), lar(_lar)
{

    std::vector<Object *> tmp_line;
    Teupor *tmp_teupor;
    Reumus *tmp_reumus;
    Streumons *tmp_streumons;
    Diams *tmp_diams;
    Geurchars *tmp_geurchar;

    for (int i = 0; i < this->hau; i++)
    {
        for (int j = 0; j < this->lar; j++)
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

            case '0':
            case '1':
            case '2':
                tmp_streumons = new Streumons((int)txt_board[i * lar + j] - 48);
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

            case 'J':
            case ' ':
                tmp_line.push_back(NULL);
                break;

            default:
                break;
            }
        }
        coord.push_back(tmp_line);
        tmp_line.clear();
    }
}

std::vector<int> Board::getRandomPoint()
{
    int point = rand() % ((lar - 2) * (hau - 2));
    std::vector<int> rd_point;
    rd_point.push_back(point / (lar - 2) + 1);
    rd_point.push_back(point % (lar - 2) + 1);
    return rd_point;
}

template <typename T>
void Board::addItems(int number)
{
    T *tmp_obj;
    while (number > 0)
    {
        std::vector<int> rd_point = getRandomPoint();

        if (coord[rd_point[0]][rd_point[1]] == NULL)
        {
            tmp_obj = new T();
            coord[rd_point[0]][rd_point[1]] = tmp_obj;
            number--;
        }
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

    for (int i = 0; i < (this->lar * this->hau) / 600 + 1; i++)
    {
        this->reumus_vert(this->hau / 3);
        this->reumus_diag(std::min(this->lar, this->hau) / 3);
        this->reumus_hor(this->hau / 3);
    }

    this->addItems<Diams>(nb_diams);
    this->addItems<Geurchars>(nb_geurchars);
    this->addItems<Streumons>(nb_streumons);
}

std::string Board::toString(bool strm_mode)
{
    std::string plateau = "";
    for (int i = 0; i < hau; i++)
    {
        for (int j = 0; j < lar; j++)
        {
            if (coord[i][j])
            {
                if (strm_mode && (coord[i][j]->getSymbol() == 's'))
                {
                    plateau += std::to_string(dynamic_cast<Streumons *>(coord[i][j])->getType());
                }
                else
                {
                    plateau.push_back(coord[i][j]->getSymbol());
                }
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

std::stringstream Board::toStream(bool strm_mode)
{
    std::stringstream boardStream(toString(strm_mode));
    return boardStream;
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
    int size = (rand() % size_max) + 4;
    std::vector<int> rd_point = getRandomPoint();

    for (int line = rd_point[0]; line < std::min(rd_point[0] + size, hau - 1); line++)
    {
        Reumus *tmp_str = new Reumus();
        coord[line][rd_point[1]] = tmp_str;
    }
}

void Board::reumus_hor(int size_max)
{
    int size = (rand() % size_max) + 4;
    std::vector<int> rd_point = getRandomPoint();

    for (int row = rd_point[1]; row < std::min(rd_point[1] + size, lar - 1); row++)
    {
        Reumus *tmp_str = new Reumus();
        coord[rd_point[0]][row] = tmp_str;
    }
}

void Board::reumus_diag(int size_max)
{
    int size = (rand() % size_max) + 4;
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

void Board::openTeupors()
{
    int dep = rand() % (lar * hau);
    bool found = false;
    int i, j;
    do
    {
        i = dep / lar;
        j = dep % lar;
        if (j == 0 || j == lar - 1 || i == 0 || i == hau - 1)
        {
            if (coord[i][j]->getSymbol() == '-')
            {
                dynamic_cast<Teupor *>(coord[i][j])->openTeupor();
                found = true;
            }
        }
        dep++;
        dep = dep % (hau * lar);

    } while (!found);
}

void Board::moveStrm(std::vector<int> old_p, std::vector<int> new_p)
{

    coord[new_p[0]][new_p[1]] = coord[old_p[0]][old_p[1]];
    coord[old_p[0]][old_p[1]] = NULL;
}

double Board::heuristicH(std::vector<int> curr, std::vector<int> dest)
{
    return ((double)sqrt((curr[0] - dest[1]) * (curr[0] - dest[1]) + (curr[1] - dest[2]) * (curr[1] - dest[2])));
}

void Board::elimination(std::vector<int> old_pos, std::vector<int> new_pos)
{
    delete coord[new_pos[0]][new_pos[1]];
    coord[new_pos[0]][new_pos[1]] = NULL;
    delete coord[old_pos[0]][old_pos[1]];
    coord[new_pos[0]][new_pos[1]] = NULL;
}

void Board::reproduction(std::vector<int> old_pos, std::vector<int> new_pos)
{
    Streumons *tmp_streums = new Streumons();
    elimination(old_pos, new_pos);               // élimination ancêtres, reproduction comme certaines espèces de poissons ..
    coord[new_pos[0]][new_pos[1]] = tmp_streums; // naissance du nouveau né !
}

void Board::fusion(std::vector<int> old_pos, std::vector<int> new_pos)
{
    int type_obj = rand() % 2;
    Geurchars *tmp_geuchars = new Geurchars();
    Diams *tmp_diams = new Diams();
    elimination(old_pos, new_pos);

    switch (type_obj)
    {
    case 0:
        coord[new_pos[0]][new_pos[1]] = tmp_diams; // parfois les bêtes produisent de belles choses ...
        break;
    case 1:
        coord[new_pos[0]][new_pos[1]] = tmp_geuchars; // parfois les bêtes produisent de belles choses ...
    default:
        break;
    }
}
