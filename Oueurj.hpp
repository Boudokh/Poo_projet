#ifndef OUEURJ_HPP
#define OUEURJ_HPP

#include "Fixed.hpp"
#include "Movable.hpp"

class Oueurj : Movable {

    private:
        char symbol;
        int state; // 0 mort, 1 en jeu, 2 gagné
        int nbr_teleport;
        int nbr_diams;
    public:
        Oueurj(int _nbr_teleport = 0, int _state = 0);
        void seTeleporter();
        void sortir();
};

#endif
