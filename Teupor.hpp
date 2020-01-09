#ifndef TEUPORS_HPP
#define TEUPORS_HPP

#include "Object.hpp"

class Teupor : public Object
{
private:
public:
    Teupor();
    ~Teupor();

    // état actuel de la porte
    char getStateTeupor() const;

    // ouverture d'une porte après que le joueur ait pris un diamant
    void openTeupor();

    virtual std::string getName();
};

#endif