#include "Oueurj.hpp"

Oueurj::Oueurj(std::vector<int> _pos, int _state, int _nb_diams, int _nb_teleport) : pos(_pos), state(_state), nb_diams(_nb_diams), nb_teleport(_nb_teleport)
{
    this->symbol = 'J';
}

Oueurj::Oueurj() : state(0), nb_diams(0), nb_teleport(0)
{
    this->pos.assign(3, 0);
    this->symbol = 'J';
}

void Oueurj::levelUp(){
    this->pos[2]++;
    
}

std::vector<int> Oueurj::getPos() const
{
    return this->pos;
}

void Oueurj::setPos(const std::vector<int> new_pos)
{
    this->pos = new_pos;
}

int Oueurj::getCurrentlevel() const { return this->pos[0]; }

Oueurj::~Oueurj() {}