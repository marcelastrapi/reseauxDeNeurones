#include <monde.hpp>

Monde::Monde(unsigned int largeur, unsigned int hauteur):
    m_largeur(largeur),
    m_hauteur(hauteur),
    m_ticDepuisCréation(0)
{ }

Coord Monde::getRoundCoord(Etre::nbType x, Etre::nbType y)
{
    // si x == -1 alors je renvois de l'autre coté etc...
    Coord rep;

    if ( x < 0 )
        x += this->m_largeur;
    else if (x >= this->m_largeur)
        x -= this->m_largeur;

    if ( y < 0 )
        y += this->m_hauteur;
    else if (y >= this->m_hauteur)
        y -= this->m_hauteur;

    rep.x = x;
    rep.y = y;
    return rep;
}

// Sub
void Monde::tic()
{
    m_ticDepuisCréation++;
    for (Etre* e: m_toutLesEtres)
        e->tic();
}
