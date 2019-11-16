#ifndef OUEURJ_HPP
#define OUEURJ_HPP

#include "Fixed.hpp"
#include "Geuchars.hpp"
#include <limits>

/*
Listing des mouvements :

    - F : reste en place
    - R : en haut
    - V : en bas
    - D : à gauche
    - G : à droite
    - E : en haut à gauche (diag)
    - T : en haut à droite (diag)
    - C : en bas à gauche (diag)
    - V : en bas à droite (diag)
*/

class Oueurj {

    private:
        char symbol;
        char move;
        int nbr_teleport;
    public:
        Oueurj(char symbol = 'J', char _move = 'F', int _nbr_teleport = 0);
        void déplacer(char _move);
        void prendre(Fixed* objet);
        void seTeleporter(Geuchars* geuchars, int _nbr_teleport = std::numeric_limits<int>::max());
        void sortir();
};

#endif
