#ifndef DIAMS_HPP
#define DIAMS_HPP

#include "Fixed.hpp"

class Diams : public Fixed {

    private:
        char symbol;
        int nbr_diams;
    public:
        Diams(char symbol = '$');
        virtual bool etrePrisPar(Diams* diamant);
        int getnbr_diams() const;
};

#endif