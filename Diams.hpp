#ifndef DIAMS_HPP
#define DIAMS_HPP

#include "Object.hpp"

class Diams : public Object {

    private:

    public:
        Diams();
        ~Diams();
        char getSymbol() const;
        virtual std::string getName();

};

#endif