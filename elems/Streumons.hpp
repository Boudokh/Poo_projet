#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Movable.hpp"

class Streumons : public Movable {

    private:
        char symbol;
        int nbr_streumons;
    public:
        Streumons(char symbol = 's');
        virtual void dévore(Oueurj* player);
        virtual void déplacer(char _move);
        getnbr_streumons() const;
};

#endif
