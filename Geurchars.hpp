#ifndef GEURCHARS_HPP
#define GEURCHARS_HPP

#include "Object.hpp"

class Geurchars : public Object {

    private:
        char symbol;
    public:
        Geurchars();
        ~Geurchars();
        char getSymbol() const;

};

#endif