#ifndef MOVABLE_HPP
#define MOVABLE_HPP
#include <vector>

#include "Object.hpp"
#include "Oueurj.hpp"

class Movable : public Object {
    private:
        std::vector<Streumons*> streumons;
    protected:
        char move;
    public:
        Movable();
        virtual char getSymbol();
        virtual void dévore(Oueurj* player);
        virtual void déplacer(Streumons* streumon, char _move);
};

#endif