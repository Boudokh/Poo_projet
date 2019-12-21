#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Movable.hpp"

class Streumons : public Movable {

    private:
        char symbol;
        int compteurMove; // Compteur permettant de calculer le coût du déplacement.
    public:
        Streumons();
        ~Streumons();
        char getSymbol() const;
        
};

#endif
