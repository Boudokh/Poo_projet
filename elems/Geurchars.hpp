#ifndef GEURCHARS_HPP
#define GEURCHARS_HPP

#include "Fixed.hpp"

class Geurchars : public Fixed {

    private:
        char symbol;
        int x_axis;
        int y_axis;
    public:
        void setSymbol(const char symbol = '*');
        int getX() const;
        int getY() const;
        void setX(const int);
        void setY(const int);
};

#endif