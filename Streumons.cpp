#include "Streumons.hpp"

Streumons::~Streumons(){
}

Streumons::Streumons()
{
    this->symbol = 's';
    this->setID(rand()%3);

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

void Streumons::setID(const int _id)
{
    this->id = _id;
}

int Streumons::getID() const {
    return this->id;
}


