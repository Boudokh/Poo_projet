#include "Oueurj.hpp"

/**
 * @brief constructeur personnalisé d'un oueurj
 * 
 * @param _pos position du oueurj
 * @param _nb_diams nombre de diams
 * @param _inf_telep option teleportation infinie active 
 * @param _nb_teleport nombre de teleportation
 * @param _state etat actuel du oueurj
 */
Oueurj::Oueurj(
    std::vector<int> _pos,
    int _nb_diams,
    bool _inf_telep,
    int _nb_teleport,
    int _vies)
    : pos(_pos), nb_diams(_nb_diams), inf_telep(_inf_telep), nb_teleport(_nb_teleport), state(0), vies(_vies)
{

    this->symbol = 'J';
}

Oueurj::Oueurj(std::vector<int> _pos, int _nb_diams, bool _inf_telep, int _nb_teleport, int _state) : pos(_pos), nb_diams(_nb_diams), inf_telep(_inf_telep), nb_teleport(_nb_teleport), state(_state)
{
    this->symbol = 'J';
}

void Oueurj::levelUp()
{
    // bonus téleportation infini désactivé à chaque passage de niveau
    this->inf_telep = false;
    this->pos[0]++;
    this->nb_teleport++;
    this->vies++;
}

std::vector<int> Oueurj::getPos() const
{
    return this->pos;
}

/**
 * @brief mise à jour de la position du oueurj sur le plateau lors d'un déplacement.
 * 
 * @param new_pos nouvelle position du Oueurj
 */
void Oueurj::setPos(const std::vector<int> new_pos)
{
    this->pos = new_pos;
}

/**
 * @brief  fonction utilisée lors du contact avec les streumons
 * @note   perte de vie ou mort si aucune vie restante
 * @retval None
 */
void Oueurj::die()
{
    if (vies > 0)
    {
        vies--;
    }
    else
    {
        this->state = -1;
    }
}

/**
 * @brief  victoire si le Oueurj atteint une porte ouverte au dernier plateau
 * @retval None
 */
void Oueurj::win()
{
    this->state = 1;
}

void Oueurj::eatDiams()
{
    this->nb_diams++;
}

/**
 * @brief utilisation de la teleportation (infinie ou par défaut dès le départ (de type compteur)).
 * 
 * @return true téléportation autorisée
 * @return false téléportation refusée
 */
bool Oueurj::teleport()
{
    // téléportation infinie.
    if (this->inf_telep)
    {
        return true;
    }
    // téléportation par défaut.
    if (this->nb_teleport > 0)
    {
        this->nb_teleport--;
        return true;
    }

    return false;
}

/**
 * @brief affichage du nombre de téléportations.
 * 
 * @return std::string à afficher dans l'écran des scores inf ou le nombre de téléportation restant
 */
std::string Oueurj::getTelep(bool for_file) const
{

    std::string tlp;
    if (for_file)
    {
        return std::to_string(this->inf_telep)+"*"+std::to_string(this->nb_teleport);
    }
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

int Oueurj::getNbDiams() const
{
    return this->nb_diams;
}


int Oueurj::getVies() const
{
    return this->vies;
}
/**
 * @brief description des la situation actuelle:
 * @note nombre de téléportation, de diams et du niveau courant, utilisé pour l'affichage du score.
 *
 * @return std::stringstream description des la situation actuelle
 */
std::stringstream Oueurj::toStream(int lvl_max) const
{
    std::stringstream score_line;
    score_line.str("    Téléports: " + getTelep() + "\n" +
                   "    Diams:     " + std::to_string(this->nb_diams) + "\n" +
                   "    Niveau:    " + std::to_string(this->pos[0] + 1) + "/" + std::to_string(lvl_max) + "\n" +
                   "    Vies:      " + std::to_string(this->vies));
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
 * @return int état courant du oueurj
 */
int Oueurj::getState() const { return this->state; }

Oueurj::~Oueurj() {}