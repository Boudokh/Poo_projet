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

int Streumons::getPosiX() const{
    return this->posi_x;
}

int Streumons::getPosiY() const{
    return this->posi_y;
}

void Streumons::setPosiX(const int _x)
{
    this->posi_x = _x;
}

void Streumons::setPosiY(const int _y)
{
    this->posi_y = _y;
}

//Streumons::Streumons(){}

