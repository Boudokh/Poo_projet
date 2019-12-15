#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Movable.hpp"

class Streumons : public Movable {

    private:
        char symbol;
        int compteurMove; // Compteur permettant de calculer le coût du déplacement.
        int posi_x; // position x du streumons.
        int posi_y; // position y du streumons.
    public:
        Streumons();
        ~Streumons();
        char getSymbol() const;
        int getPosiX() const;
        int getPosiY() const;
        void setPosiX(const int);
        void setPosiY(const int);
};

#endif
