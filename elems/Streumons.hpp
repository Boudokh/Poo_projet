#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Movable.hpp"

class Streumons : public Movable {

    private:
        char symbol;
        int nbr_streumons;
    public:
        Streumons(char symbol = 's');
        virtual void déplacer(char _move);
        int getnbr_streumons() const;
        virtual char getSymbol() const;

};

#endif
