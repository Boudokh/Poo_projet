#ifndef DIAMS_HPP
#define DIAMS_HPP

#include "Fixed.hpp"

class Diams : public Fixed {

    private:

    public:
        Diams();
        ~Diams();
        char getSymbol() const;
        virtual std::string  getName(); //à améliorer

};

#endif