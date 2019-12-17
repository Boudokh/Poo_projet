#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <typeinfo>
#include <string>
#include <vector>

class Object
{

protected:
    char symbol;

private:
public:
    virtual ~Object();
    virtual char getSymbol() const;
    virtual std::string  getName();
};

#endif