#include "Oueurj.hpp"

/**
 * @brief constructeur d'un oueurj
 * 
 * @param _pos position du oueurj
 * @param _nb_diams nombre de diams
 * @param _inf_telep option teleportation infinie active 
 * @param _nb_teleport nombre de teleportation
 * @param _state etat actuel du oueurj
 */

Oueurj::Oueurj(std::vector<int> _pos, int _nb_diams, bool _inf_telep, int _nb_teleport, int _state) : pos(_pos), nb_diams(_nb_diams), inf_telep(_inf_telep), nb_teleport(_nb_teleport), state(_state)
{
    this->symbol = 'J';
}

void Oueurj::levelUp()
{
    this->inf_telep = false;
    this->pos[0]++;
}

std::vector<int> Oueurj::getPos() const
{
    return this->pos;
}

void Oueurj::setPos(const std::vector<int> new_pos)
{
    this->pos = new_pos;
}

void Oueurj::die()
{
    this->state = -1;
}

void Oueurj::win()
{
    this->state = 1;
}

void Oueurj::eatDiams()
{
    this->nb_diams++;
}

bool Oueurj::teleport()
{
    if (this->inf_telep)
    {
        return true;
    }

    if (this->nb_teleport > 0)
    {
        this->nb_teleport--;
        return true;
    }

    return false;
}

std::string Oueurj::getTelep() const
{

    std::string tlp;
    if (this->inf_telep)
    {
        tlp = "inf";
    }
    else
    {
        tlp = std::to_string(this->nb_teleport);
    }

    return tlp;
}

int Oueurj::getNbDiams()
{
    return this->nb_diams;
}

/**
 * @brief affichage sur la console du nombre de téléportation, de diams et du niveau courant à droite du plateau.
 * 
 * @return std::stringstream 
 */

std::stringstream Oueurj::toStream() const
{
    std::stringstream score_line;
    score_line.str("    Téléports: " + getTelep() + "\n" +
                   "    Diams:     " + std::to_string(this->nb_diams) + "\n" +
                   "    Niveau:    " + std::to_string(this->pos[0] + 1));
    return score_line;
}

/**
 * @brief activation de l'option teleportation infinie
 * 
 */

void Oueurj::switch_teleport()
{
    this->inf_telep = true;
}

int Oueurj::getCurrentlevel() const { return this->pos[0]; }

/**
 * @brief état courant du oueurj
 * 
 * @return int 
 */
int Oueurj::getState() const { return this->state; }

Oueurj::~Oueurj() {}