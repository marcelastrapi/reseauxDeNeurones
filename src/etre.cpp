#include <etre.hpp>

#include <cmath> // pour atan2f()

// ctor
Etre::Etre(): 
    m_pos(Coord(0,0)),
    m_forme(Rectangle),
    m_couleur(Couleur(0,0,0)),
    m_largeurDuMonde(0), m_hauteurDuMonde(0),
    m_largeur(1), m_hauteur(1),
    m_angleDeRotation(0),
    m_mouvant(false),
    m_maxAngleDeRotation(360),
    m_maxDistanceDeDeplacement(0)
{ }

// debug
void Etre::debug() const
{
    note("_______________________________________________________");
    note("pos:" + to_string(m_pos.x) + "," + to_string(m_pos.y) );
    note("dimension: " + to_string(m_largeur) + ',' + to_string(m_hauteur) );
    note("dimensionDuMonde: " + to_string(m_largeurDuMonde) + ',' + to_string(m_hauteurDuMonde) );
    note("couleur:" + m_couleur.toString());
    note("m_maxDistanceDeDeplacement:" + to_string(m_maxDistanceDeDeplacement));
    note("m_maxAngleDeRotation:" + to_string(m_maxAngleDeRotation));
    note("m_angleDeRotation:" + to_string(m_angleDeRotation));
}

// setters
void Etre::setDimensionDuMonde(const nbType largeur, const nbType hauteur)
{
    m_largeurDuMonde = largeur;
    m_hauteurDuMonde = hauteur;
}

void Etre::setLeft(const nbType left)
{
    m_pos.x = left;
    if (left < 0) m_pos.x = 0;
    if (getRight() >= m_largeurDuMonde) setRight(m_largeurDuMonde-1);
}
void Etre::setTop(const nbType top)
{
    m_pos.y = top;
    if (top < 0) m_pos.y  = 0;
    if (getBottom() >= m_hauteurDuMonde) setBottom(m_hauteurDuMonde-1);
}

void Etre::setAngle(const nbType angle)
{

    /* if (dist(angle,m_angleDeRotation) > m_maxAngleDeRotation) */
    /*     angle = m_maxAngleDeRotation */

    m_angleDeRotation = angle;

}

void Etre::setDimension(const nbType largeur, const nbType hauteur)
{
    m_largeur = largeur;
    m_hauteur = hauteur;
}


// functions 
Etre::angleType Etre::getAngleEntreMoiEt(const Etre* lui) const
{
    auto pos = lui->getPos();
    Etre::nbType delta_x = pos.x - m_pos.x;
    Etre::nbType delta_y = m_pos.y - pos.y;
    return atan2f(delta_y, delta_x) ;
}

// sub
void Etre::avance(Etre::nbType distanceDeDeplacement)
{
    if (distanceDeDeplacement > m_maxDistanceDeDeplacement)
        distanceDeDeplacement = m_maxDistanceDeDeplacement;

    Etre::nbType xDepl = distanceDeDeplacement * cosf(m_angleDeRotation);
    Etre::nbType yDepl = distanceDeDeplacement * sinf(m_angleDeRotation);

    /* show("cos(" + to_string(m_angleDeRotation) + ")",cosf(m_angleDeRotation)); */
    /* show("sin(" + to_string(m_angleDeRotation) + ")",-sinf(m_angleDeRotation)); */
    /* show("xDepl",xDepl); */
    /* show("yDepl",yDepl); */

    setPos(m_pos.x + xDepl, m_pos.y - yDepl);

}
void Etre::reborn()
{
    m_pos = Coord( static_cast<float>(Rnd::_int( 0, static_cast<int>(getMaxPosX()) )),\
                   static_cast<float>(Rnd::_int( 0, static_cast<int>(getMaxPosY()) )) );
}
