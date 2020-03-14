#include <poisson.hpp>
#include <cmath>
#include <utils.hpp>

Poisson::Poisson() :
    m_minRnd(-3.14f),
    m_maxRnd(3.14f)
{
    m_forme = Cercle;
    initialiseLesVariablesAléatoires();
}

// sub
void Poisson::calculeNouvelleAngle()
{
    m_angleDeDirection = 3.14f;
}

/////////// OVERRIDE
void Poisson::reborn()
{
    // reset ma pos
    Etre::reborn();
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
    for (auto& varAlea : m_variablesAléatoires)
        varAlea = static_cast<Etre::nbType>( Rnd::_double()*3.14 );
}
