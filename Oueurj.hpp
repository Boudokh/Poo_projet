#ifndef OUEURJ_HPP
#define OUEURJ_HPP

#include "Object.hpp"

class Oueurj : public Object
{

private:
    std::vector<int> pos;
    int state; // 0 en jeu, 1mort,  2 gagné
    int nb_diams;
    int nb_teleport;

public:
    Oueurj(std::vector<int> _pos, int _state = 0, int _nb_diams = 0, int _nb_teleport = 0);
    Oueurj();
    void setPos(const std::vector<int> new_pos);
    std::vector<int> getPos() const;
    int getCurrentlevel() const;
    ~Oueurj();
};

#endif
