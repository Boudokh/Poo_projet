#ifndef STREUMONS_HPP
#define STREUMONS_HPP

#include "Movable.hpp"

class Streumons : public Movable {

    private:
        char symbol;
        int x_axis;
        int y_axis;

    public:
        void setSymbol(const char symbol = 's');
        int getX() const;
        int getY() const;
        void setX(const int);
        void setY(const int);
};

#endif
