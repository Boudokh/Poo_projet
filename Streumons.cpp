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

