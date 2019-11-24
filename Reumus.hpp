#ifndef REUMUS_HPP
#define REUMUS_HPP
#include <cstdlib>
#include "Fixed.hpp"

class Reumus : public Fixed
{

private:
public:
    Reumus();
    virtual std::string  getName(); //à améliorer
};

#endif