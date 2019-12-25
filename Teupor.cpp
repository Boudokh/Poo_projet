#include "Teupor.hpp"

Teupor::Teupor()
{
    this->symbol = '-';
}
std::string Teupor::getName()
{
    return typeid(this).name();
}

Teupor::~Teupor() {}

void Teupor::openTeupor()
{
    this->symbol = '+';
}
