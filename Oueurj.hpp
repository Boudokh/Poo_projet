#ifndef OUEURJ_HPP
#define OUEURJ_HPP

#include "Fixed.hpp"
#include "Geuchars.hpp"
#include "Movable.hpp"

class Oueurj : Movable {

    private:
        char symbol;
        char move;
        int state; // 0 mort, 1 en jeu, 2 gagné
        int nbr_teleport;
        int nbr_diams;
    public:
        Oueurj(char symbol = 'J', char _move = 'F', int _nbr_teleport = 0, int _state = 0);
        void prendre(Fixed* objet);
        void seTeleporter(Geuchars* geuchars, int _nbr_teleport = 100000000);
        void sortir();
};

#endif
