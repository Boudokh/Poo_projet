#ifndef TEUPORS_HPP
#define TEUPORS_HPP

#include "Fixed.hpp"

class Teupor : public Fixed {

    private:
    public:
        Teupor(); /* par défaut la porte est fermée */
        char getStateTeupor() const; /* état courante de la porte */
        void openTeupor(); /* ouverture d'une porte après que le joueur ait pris un diamant */
};

#endif