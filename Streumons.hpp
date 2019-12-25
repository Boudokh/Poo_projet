#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Movable.hpp"

class Streumons : public Movable {

    private:
        char symbol;
        int type; // type statégie stremons : 0 (random) , 1 (A*)
        int type_evol; // type quand deux stremons se rencontrent : élimination, reproduction par % au type.
    public:
        Streumons();
        ~Streumons();
        char getSymbol() const;
        int getType() const;
        int getTypeEvol() const;
        
};

#endif
