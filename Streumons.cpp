#include "Streumons.hpp"

Streumons::~Streumons(){
}

Streumons::Streumons()
{
    this->symbol = 's';
}

char Streumons::getSymbol() const {
    return this->symbol;
}

void Streumons::setType(const int streumons_type) 
{
    this->type = streumons_type;
}

int Streumons::getType() const
{
    return this->type;
}



