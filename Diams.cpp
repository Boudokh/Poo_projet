#include "Diams.hpp"

Diams::Diams()
{
    this->symbol = '$';
}
Diams::~Diams() {}

char Diams::getSymbol() const
{
    return this->symbol;
}

std::string Diams::getName()
{
    return typeid(this).name();
}