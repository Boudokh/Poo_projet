#ifndef FIXED_HPP
#define FIXED_HPP

#include <vector>
#include "Object.hpp"
#include "Oueurj.hpp"

class Diams;
class Reumus;
class Geurchars;
class Teupors;

class Fixed : public Object {

    private:
        std::vector<Diams*> diams;
        std::vector<Reumus*> reumus;
        std::vector<Geurchars*> geuchars;
        std::vector<Teupors*> teupors;
    protected:

    public:
        Fixed();
        virtual bool etrePrisPar(Oueurj* joueur);
};

#endif