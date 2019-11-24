#ifndef GEURCHARS_HPP
#define GEURCHARS_HPP

#include "Fixed.hpp"

class Geurchars : public Fixed {

    private:
        char symbol;
    public:
        Geurchars();
        void setTeleport(int _nbr); // Quand le joueur prend un geuchar, teleportation infini
        ~Geurchars();

};

#endif