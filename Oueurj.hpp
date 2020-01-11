#ifndef OUEURJ_HPP
#define OUEURJ_HPP

#include "Object.hpp"
#include <sstream>

class Oueurj : public Object
{

private:
    std::vector<int> pos; // position du oueurj (label plateau, i , j)
    int nb_diams;
    bool inf_telep; // teleportation infinie
    int nb_teleport;
    int state; // 0 en jeu, -1 mort, 1 gagné

public:

    Oueurj(std::vector<int> _pos, int _nb_diams = 0, bool _inf_telep = false, int _nb_teleport = 0, int _state = 0);
    Oueurj();
    ~Oueurj();

    void levelUp();

    // déplacement du oueurj sur le plateau.
    void setPos(const std::vector<int> new_pos);

    // récupération de la position du oueurj sur le plateau.
    std::vector<int> getPos() const;

    int getCurrentlevel() const;

    // utilisation de la téléportation.

    bool teleport();

    // activation de la téléportation.

    void switch_teleport();

    void die();
    void win();

    // affichage du nombre de téléportations.

    std::string getTelep() const;


    int getNbDiams();

    // état courant du oueurj.

    int getState() const;

    // affichage du nombre de téléportations, de diams et du niveau actuel.

    std::stringstream toStream() const;

    void eatDiams();
};

#endif
