#include "Geurchars.hpp"

Geurchars::~Geurchars() {}

Geurchars::Geurchars()
{
    this->symbol = '*';
}

char Geurchars::getSymbol() const
{
    return this->symbol;
}