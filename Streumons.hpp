#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Object.hpp"

class Streumons : public Object
{

private:
    char symbol;
    int type;     // type statégie streumons : 0 (random) , 1 (A*)
    int typeevol; // type interraction streumons : elimination (0) , reproduction (1), fusion(2).

public:
    Streumons();
    Streumons(int _type);
    ~Streumons();

    char getSymbol() const;
    int getType() const;
    int getTypeEvol() const;
};

#endif
