#ifndef REUMUS_HPP
#define REUMUS_HPP
#include <cstdlib>
#include "Object.hpp"

class Reumus : public Object
{
private:
public:
    Reumus();
    virtual std::string getName();
    virtual char getSymbol() const;
    ~Reumus();
};

#endif