#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Movable.hpp"

class Streumons : public Movable {

    private:
        char symbol;
        int compteurMove; // Compteur permettant de calculer le coût du déplacement.
        int posi_x; // position x du streumons.
        int posi_y; // position y du streumons.
        int id; // identifiant pour le streumons : classe 0 (MODE Poursuite) , classe 1 (MODE Defense diams), classe 2 (MODE Defense geuchars)
    public:
        Streumons();
        ~Streumons();
        char getSymbol() const;
        int getPosiX() const;
        int getPosiY() const;
        void setPosiX(const int);
        void setPosiY(const int);
        int getID() const;
        void setID(const int);
};

#endif
