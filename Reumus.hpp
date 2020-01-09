#ifndef REUMUS_HPP
#define REUMUS_HPP
#include <cstdlib>
#include "Object.hpp"

class Reumus : public Object
{
private:
public:
    Reumus();
    virtual std::string getName(); //à améliorer
    virtual char getSymbol() const;
    ~Reumus();
};

#endif