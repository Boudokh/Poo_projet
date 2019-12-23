#include "Reumus.hpp"

Reumus::Reumus(){
    this->symbol = 'X';

}

std::string Reumus:: getName() const
{
    return typeid(this).name();
}

Reumus::~Reumus(){}

char Reumus::getSymbol() const{
    return this->symbol;
}



