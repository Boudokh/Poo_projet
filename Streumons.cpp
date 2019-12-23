#include "Streumons.hpp"

Streumons::~Streumons()
{
}

Streumons::Streumons()
{
    int _type_streums = rand() % 3;
    this->symbol = 's';
    this->type = _type_streums;
}

char Streumons::getSymbol() const
{
    return this->symbol;
}

int Streumons::getType() const
{
    return this->type;
}
