#include <poisson.hpp>
#include <cmath>
#include <utils.hpp>

Poisson::Poisson() :
    m_minRnd(-3.14),
    m_maxRnd(3.14)
{
    m_forme = Cercle;
    initialiseLesVariablesAléatoires();
}

// sub
void Poisson::calculeNouvelleAngle()
{

    /* show("cl",cl); */
    // en fonction de la pos du requin
    /* m_angleDeDirection = m_variablesAléatoires.at(0) * m_requin->getPos().x/m_largeurDuMonde \ */
    /*         + m_variablesAléatoires.at(1) * m_requin->getPos().y/m_hauteurDuMonde - 3.14; */
    /* show("var0",m_variablesAléatoires[0]); */
    /* show("var1",m_variablesAléatoires[1]); */
    /* show("m_angleDeDirection",m_angleDeDirection); */
    /* m_angleDeDirection = -3.14/2; */
}

/////////// OVERRIDE
void Poisson::reborn()
{
    // reset ma pos
    /* Etre::reborn(); */
    /* m_maxDistanceDeDeplacement = m_requin->getMaxDistanceDeDeplacement(); */
    initialiseLesVariablesAléatoires();
    calculeNouvelleAngle();
}

// debug
void Poisson::debug() const
{
    Etre::debug();
    note("Je suis un poisson");
}

//////////////////////////////////////////////////////// PRIVATE
void Poisson::initialiseLesVariablesAléatoires()
{
    /* for (auto& varAlea : m_variablesAléatoires) */
    /*     varAlea = static_cast<Etre::nbType>( Rnd::_double()*3.14 ); */

}
