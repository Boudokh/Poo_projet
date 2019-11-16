#ifndef TEUPORS_HPP
#define TEUPORS_HPP

#include "Fixed.hpp"

class Teupors : public Fixed {

    private:
        char symbol;
        int x_axis;
        int y_axis;
    public:
        void setOpenTeupors(const char symbol = '+');
        void setCloseTeupors(const char symbol = '-');
        char getStateTeupors() const;
        int getX() const;
        int getY() const;
        void setX(const int);
        void setY(const int);       
};

#endif