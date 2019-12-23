#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Movable.hpp"

class Streumons : public Movable {

    private:
        char symbol;
        int type; // type statégie stremons : 0 (random) , 1 (A*)
    public:
        Streumons();
        virtual ~Streumons();
        char getSymbol() const;
        int getType() const;
        
};

#endif
