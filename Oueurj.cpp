#include "Oueurj.hpp"

Oueurj::Oueurj(
    std::vector<int> _pos,
    int _nb_diams,
    bool _inf_telep,
    int _nb_teleport,
    int _vies)
    : pos(_pos), nb_diams(_nb_diams), inf_telep(_inf_telep), nb_teleport(_nb_teleport), state(0), vies(_vies)
{

    this->symbol = 'J';
}

Oueurj::Oueurj() : nb_diams(0), nb_teleport(0), state(0)
{
    this->pos.assign(3, 0);
    this->symbol = 'J';
}

void Oueurj::levelUp()
{
    this->inf_telep = false;
    this->pos[0]++;
    this->nb_teleport++;
    this->vies++;
}

std::vector<int> Oueurj::getPos() const
{
    return this->pos;
}

void Oueurj::setPos(const std::vector<int> new_pos)
{
    this->pos = new_pos;
}

void Oueurj::die()
{
    if (vies > 0)
    {
        vies--;
    }
    else
    {
        this->state = -1;
    }
}

void Oueurj::win()
{
    this->state = 1;
}

void Oueurj::eatDiams()
{
    this->nb_diams++;
}

bool Oueurj::teleport()
{
    if (this->inf_telep)
    {
        return true;
    }

    if (this->nb_teleport > 0)
    {
        this->nb_teleport--;
        return true;
    }

    return false;
}

std::string Oueurj::getTelep(bool for_file) const
{

    std::string tlp;
    if (for_file)
    {
        return std::to_string(this->inf_telep)+"*"+std::to_string(this->nb_teleport);
    }
    if (this->inf_telep)
    {
        tlp = "inf";
    }
    else
    {
        tlp = std::to_string(this->nb_teleport);
    }

    return tlp;
}

int Oueurj::getNbDiams() const
{
    return this->nb_diams;
}

int Oueurj::getVies() const
{
    return this->vies;
}

std::stringstream Oueurj::toStream(int lvl_max) const
{
    std::stringstream score_line;
    score_line.str("    Téléports: " + getTelep() + "\n" +
                   "    Diams:     " + std::to_string(this->nb_diams) + "\n" +
                   "    Niveau:    " + std::to_string(this->pos[0] + 1) + "/" + std::to_string(lvl_max) + "\n" +
                   "    Vies:      " + std::to_string(this->vies));
    return score_line;
}

void Oueurj::switch_teleport()
{
    this->inf_telep = true;
}

int Oueurj::getCurrentlevel() const { return this->pos[0]; }

int Oueurj::getState() const { return this->state; }

Oueurj::~Oueurj() {}