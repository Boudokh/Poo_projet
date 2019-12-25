#include "Streumons.hpp"

Streumons::~Streumons()
{
}

Streumons::Streumons()
{
    int _type_streums = rand() % 3;
    int _type_evol = rand() % 2;
    this->symbol = 's';
    this->type = _type_streums;
    this->type_evol = _type_evol;
}

char Streumons::getSymbol() const
{
    return this->symbol;
}

int Streumons::getType() const
{
    return this->type;
}

int Streumons::getTypeEvol() const
{
    return this->type_evol;
}

