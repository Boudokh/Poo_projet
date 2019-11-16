#ifndef TEUPORS_HPP
#define TEUPORS_HPP

#include "Fixed.hpp"
#include "Oueurj.hpp"
#include "Diams.hpp"

class Teupors : public Fixed {

    private:
        char symbol;
    public:
        Teupors(char symbol = '-'); /* par défaut la porte est fermée */
        char getStateTeupors() const; /* état courante de la porte */
        void openTeupors(Diams* diamant); /* ouverture d'une porte après que le joueur ait pris un diamant */     
};      

#endif