#ifndef OUEURJ_HPP
#define OUEURJ_HPP

#include "Object.hpp"

class Oueurj : public Object
{

private:
    std::vector<int> pos;
    int state; // 0 en jeu, -1 mort, 1 gagné
    int nb_diams;
    int nb_teleport;
    bool inf_telep;

public:
    Oueurj(std::vector<int> _pos, int _state = 0, int _nb_diams = 0, int _nb_teleport = 0, bool _inf_telep = false);
    Oueurj();
    void levelUp();
    void setPos(const std::vector<int> new_pos);
    std::vector<int> getPos() const;
    int getCurrentlevel() const;
    void switch_teleport();
    void die();
    void win();
    ~Oueurj();
};

#endif
