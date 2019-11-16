#ifndef DIAMS_HPP
#define DIAMS_HPP

#include "Fixed.hpp"

class Diams : public Fixed {

    private:
        char symbol;
        int x_axis;
        int y_axis;
    public:
        void setSymbol(const char symbol = '$');
        int getX() const;
        int getY() const;
        void setX(const int);
        void setY(const int);
};

#endif