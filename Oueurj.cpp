#include "Oueurj.hpp"

Oueurj::Oueurj(std::vector<int> _pos, int _nb_diams, int _nb_teleport, bool _inf_telep, int _state) : pos(_pos), nb_diams(_nb_diams), nb_teleport(_nb_teleport), inf_telep(_inf_telep), state(_state)
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
    this->pos[0]++;
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
    this->state = -1;
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

std::string Oueurj::getTelep() const
{

    std::string tlp;
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

std::stringstream Oueurj::toStream() const
{
    std::stringstream score_line;
    score_line.str("    Téléports: " + getTelep() + "\n" +
                   "    Diams:     " + std::to_string(this->nb_diams) + "\n" +
                   "    Niveau:    " + std::to_string(this->pos[0] + 1));
    return score_line;
}

void Oueurj::switch_teleport()
{
    this->inf_telep = true;
}

int Oueurj::getCurrentlevel() const { return this->pos[0]; }

Oueurj::~Oueurj() {}