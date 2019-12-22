#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Movable.hpp"

class Streumons : public Movable {

    private:
        char symbol;
        int type; // type statégie stremons : 0 (random) , 1 (A*)
    public:
        Streumons();
        ~Streumons();
        char getSymbol() const;
        void setType(const int);
        int getType() const;
        
};

#endif
