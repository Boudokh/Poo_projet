#ifndef MOVABLE_HPP
#define MOVABLE_HPP
#include <vector>

#include "Object.hpp"
#include "Oueurj.hpp"

class Movable : public Object {
    private:
    protected:
        char move;
    public:
        Movable();
        virtual char getSymbol() const;
        virtual void déplacer(char _move);
};

#endif