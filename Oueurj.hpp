#ifndef OUEURJ_HPP
#define OUEURJ_HPP

#include "Object.hpp"
#include <sstream>

class Oueurj : public Object
{

private:
    std::vector<int> pos;
    int nb_diams;
    bool inf_telep;
    int nb_teleport;
    int state; // 0 en jeu, -1 mort, 1 gagné
    int vies;

public:
    Oueurj(std::vector<int> _pos, int _nb_diams = 0, bool _inf_telep = false, int _nb_teleport = 2, int _vies = 3);
    Oueurj();
    ~Oueurj();

    void levelUp();

    void setPos(const std::vector<int> new_pos);
    std::vector<int> getPos() const;
    int getCurrentlevel() const;
    bool teleport();
    void switch_teleport();

    void die();
    void win();

    std::string getTelep(bool for_file = false) const;
    int getNbDiams() const;
    int getState() const;
    int getVies() const;

    std::stringstream toStream(int lvl_max) const;
    void eatDiams();
};

#endif
