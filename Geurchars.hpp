#ifndef GEURCHARS_HPP
#define GEURCHARS_HPP

#include "Object.hpp"

class Geurchars : public Object {

    private:
        char symbol;
    public:
        Geurchars();
        //void setTeleport(int _nbr); // Quand le joueur prend un geuchar, teleportation infini
        ~Geurchars();
        char getSymbol() const;

};

#endif