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

void Streumons::setID(const int _id)
{
    this->id = _id;
}

int Streumons::getID() const {
    return this->id;
}

void Streumons::setPosiX(const int _x) {
    this->pos_x = _x;
}

void Streumons::setPosiY(const int _y){
    this->pos_y = _y;
}

int Streumons::getPosiX() const {
    return this->pos_x;
}

int Streumons::getPosiY() const {
    return this->pos_y;
}
