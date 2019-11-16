#ifndef GEURCHARS_HPP
#define GEURCHARS_HPP

#include "Fixed.hpp"

class Geurchars : public Fixed {

    private:
        char symbol;
        int nbr_teleport;
        int nbr_geuchars;

    public:
        Geurchars(char symbol = '*');
        virtual bool etrePrisPar(Oueurj* joueur);
        void setTeleport(int _nbr); /* Quand le joueur prend un geuchar, teleportation infini  */
        int getnbr_teleport() const;
        int getnbr_geuchars() const;
};  

#endif