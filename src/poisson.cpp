#include <poisson.hpp>
#include <cmath>
#include <utils.hpp>

Poisson::Poisson() :
    m_maxTempsDeVie(0),
    /* m_oldTempsDeVie(0), */
    m_epochNaissance(std::time(nullptr)),
    m_minRnd(-3.14f),
    m_maxRnd(3.14f)
{
    m_forme = Cercle;
    initialiseLesVariablesAléatoires();
}

// sub
void Poisson::calculeNouvelleAngle(const Etre::nbType directionRequin)
{
    m_angleDeDirection = directionRequin + m_variablesAléatoires[0];
}

/////////// OVERRIDE
void Poisson::renaît()
{
    // reset ma pos
    Etre::renaît();
    auto nouvelleEpoch = std::time(nullptr);
    auto tempsDeVie = nouvelleEpoch - m_epochNaissance;
    if (tempsDeVie > m_maxTempsDeVie) 
        m_maxTempsDeVie = tempsDeVie;
    else
        m_variablesAléatoires[0] += 0.1;

    /* m_oldTempsDeVie = tempsDeVie; */
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
        varAlea = static_cast<Etre::nbType>( Rnd::_double()*3.14*2 - 3.14 );
}
