#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include "Object.hpp"

class Movable : public Object {
    private:
    protected:
        char move;
    public:
        Movable();
};

#endif