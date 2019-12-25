#include "Object.hpp"

char Object::getSymbol() const
{
    return this->symbol;
}
std::string Object::getName()
{
    return typeid(this).name();
}

Object::~Object(){ std::cout << "obj dest" <<std::endl;}