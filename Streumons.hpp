#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Movable.hpp"

class Streumons : public Movable {

    private:
        char symbol;
    public:
        Streumons();
        ~Streumons();
        char getSymbol() const;
        
};

#endif
