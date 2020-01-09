#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Object.hpp"

class Streumons : public Object {

    private:
        char symbol;
        int type; // type statégie stremons : 0 (random) , 1 (A*)
        int typeevol; // elimination (0) , reproduction (1).
    public:
        Streumons();
        ~Streumons();
        char getSymbol() const;
        int getType() const;
        int getTypeEvol() const;
        
};

#endif
