#include "Object.hpp"

char Object::getSymbol() const
{
    return this->symbol;
}
std::string Object::getName() const
{
    return typeid(this).name();
}

Object::~Object(){}