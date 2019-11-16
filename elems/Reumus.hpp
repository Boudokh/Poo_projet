#ifndef REUMUS_HPP
#define REUMUS_HPP

#include "Fixed.hpp"

class Reumus : public Fixed {

    private:
        char symbol;
        int x_axis;
        int y_axis;
    public:
        void setSymbol(const char symbol = 'X');
        int getX() const;
        int getY() const;
        void setX(const int);
        void setY(const int);
};

#endif