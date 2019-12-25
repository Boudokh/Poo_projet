#ifndef OUEURJ_HPP
#define OUEURJ_HPP

#include "Movable.hpp"
#include <sstream>

class Oueurj : public Movable
{

private:
    std::vector<int> pos;
    int nb_diams;
    bool inf_telep;
    int nb_teleport;
    int state; // 0 en jeu, -1 mort, 1 gagné

public:
    Oueurj(std::vector<int> _pos, int _nb_diams = 0, bool _inf_telep = false, int _nb_teleport = 0,  int _state = 0);
    Oueurj();

    void levelUp();

    void setPos(const std::vector<int> new_pos);
    std::vector<int> getPos() const;
    int getCurrentlevel() const;
    bool teleport();
    void switch_teleport();

    void die();
    void win();

    std::string getTelep() const;
    int getNbDiams();

    int getState() const;
    std::stringstream toStream() const;
    void eatDiams();
    ~Oueurj();
};

#endif
