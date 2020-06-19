#include <etre.hpp>

#include <cmath> // pour atan2f()

// ctor
Etre::Etre(): 
    m_pos(Coord(0,0)),
    m_forme(Rectangle),
    m_couleur(Couleur(0,0,0)),
    m_largeurDuMonde(0), m_hauteurDuMonde(0),
    m_largeur(1), m_hauteur(1),
    m_largDiv(0), m_hautDiv(0),
    m_estMouvant(false),
    m_maxDistanceDeDeplacement(0),
    m_angleDeDirection(0),
    m_maxAngleDeDirection(360),
    m_estVivant(false),
    m_tempsDeVie(0),
    m_réseauDeNeurones()
{ }

// debug
void Etre::print() const
{
    note("_______________________________________________________");
    note("pos:" + to_string(m_pos.x) + "," + to_string(m_pos.y) );
    note("dimension: " + to_string(m_largeur) + ',' + to_string(m_hauteur) );
    note("dimensionDuMonde: " + to_string(m_largeurDuMonde) + ',' + to_string(m_hauteurDuMonde) );
    note("couleur:" + m_couleur.toString());
    note("m_maxDistanceDeDeplacement:" + to_string(m_maxDistanceDeDeplacement));
    note("m_maxAngleDeDirection:" + to_string(m_maxAngleDeDirection));
    note("m_angleDeDirection:" + to_string(m_angleDeDirection));
}

// setters
void Etre::dimensionDuMonde(const nbType largeur, const nbType hauteur)
{
    m_largeurDuMonde = largeur;
    m_hauteurDuMonde = hauteur;
}
void Etre::dimension(const nbType _largeur, const nbType _hauteur)
{
    largeur(_largeur);
    hauteur(_hauteur);
}

void Etre::posAléa()
{
    left(static_cast<float>( Rnd::_int( 
                static_cast<int>(0),
                static_cast<int>(m_largeurDuMonde - m_largeur) 
                )));
    top(static_cast<float>( Rnd::_int( 
                static_cast<int>(0),
                static_cast<int>(m_hauteurDuMonde - m_hauteur) 
                )));
}

void Etre::left(const nbType _left)
{
    m_pos.x = _left + m_largDiv;
    /* if (left() < 0 or right() >= m_largeurDuMonde) renaît(); */
    if (left() < 0) left(0);
    if (right() >= m_largeurDuMonde) right(m_largeurDuMonde-1);
}
void Etre::top(const nbType _top)
{
    m_pos.y = _top + m_hautDiv;
    /* if (top() < 0 or bottom() >= m_hauteurDuMonde) renaît(); */
    if (top() < 0) top(0);
    if (bottom() >= m_hauteurDuMonde) bottom(m_hauteurDuMonde-1);
}

void Etre::largeur(const nbType largeur)
{
    m_largeur = largeur;
    m_largDiv = largeur*0.5f;
}
void Etre::hauteur(const nbType hauteur)
{
    m_hauteur = hauteur;
    m_hautDiv = hauteur*0.5f;
}

void Etre::angleDeDirection(const nbType angle)
{

    /* auto distance = dist(min(angle,m_angleDeDirection),max(angle,m_angleDeDirection)); */


    /* if ( distance > m_maxAngleDeDirection) */
    /* { */
    /*     /1* note("________________________________________"); *1/ */
    /*     /1* show("m_angleDeDirection",m_angleDeDirection); *1/ */
    /*     /1* show("angle",angle); *1/ */
    /*     /1* show("distance",distance); *1/ */
    /*     if (distance > 3.14) */
    /*         m_angleDeDirection += m_maxAngleDeDirection; */
    /*     else */
    /*         m_angleDeDirection -= m_maxAngleDeDirection; */
    /* } */
    /* else */
        m_angleDeDirection = angle;

}

// réseaux de neurones

// functions 
Etre::angleType Etre::getAngleEntreMoiEt(const Etre* lui) const
{
    auto pos = lui->pos();
    Etre::nbType delta_x = pos.x - m_pos.x;
    Etre::nbType delta_y = m_pos.y - pos.y;
    return atan2f(delta_y, delta_x) ;
}

// sub
void Etre::avance(Etre::nbType distanceDeDeplacement)
{
    if (!m_estMouvant) return;

    if (distanceDeDeplacement > m_maxDistanceDeDeplacement)
        distanceDeDeplacement = m_maxDistanceDeDeplacement;

    Etre::nbType xDepl = distanceDeDeplacement * cosf(m_angleDeDirection);
    Etre::nbType yDepl = distanceDeDeplacement * sinf(m_angleDeDirection);

    /* show("cos(" + to_string(m_angleDeDirection) + ")",cosf(m_angleDeDirection)); */
    /* show("sin(" + to_string(m_angleDeDirection) + ")",-sinf(m_angleDeDirection)); */
    /* show("xDepl",xDepl); */
    /* show("yDepl",yDepl); */

    pos(m_pos.x + xDepl, m_pos.y - yDepl);

}

void Etre::renaît()
{
    posAléa();
    m_tempsDeVie = 0;
}

void Etre::tic()
{
    if (m_estVivant)
    {
        m_tempsDeVie++;
        if (m_estMouvant) avance();
    }
}
