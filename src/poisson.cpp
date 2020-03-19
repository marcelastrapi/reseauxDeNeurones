#include <poisson.hpp>

Poisson::Poisson()
{
    m_estMouvant = true;
    m_estVivant = true;
    m_forme = Cercle;
}

// sub
void Poisson::calculeNouvelleAngle(const Etre::nbType directionRequin)
{
    m_angleDeDirection = -directionRequin;
}

/////////// OVERRIDE
void Poisson::renaît()
{
    // reset ma pos
    Etre::renaît();
}

// print
void Poisson::print() const
{
    Etre::print();
    note("Je suis un poisson");
    show("Je suis vivant depuis",m_tempsDeVie);
}

//////////////////////////////////////////////////////// PRIVATE
