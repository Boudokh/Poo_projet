#ifndef REUMUS_HPP
#define REUMUS_HPP
#include <iostream>
#include <cstdlib>
#include "Fixed.hpp"

class Reumus : public Fixed {

    private:
        char symbol;
        int nbr_reumus;
    public:
        Reumus(char symbol = 'X');
        int getnbr_reumus() const;
};


#endif