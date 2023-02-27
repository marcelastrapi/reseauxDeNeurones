#include <poisson.hpp>

Poisson::Poisson(): m_plusGrandTempsDeVie(0)
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

    if (m_tempsDeVie > m_plusGrandTempsDeVie)
        m_plusGrandTempsDeVie = m_tempsDeVie;

    // reset ma pos
    Etre::renaît();
}

// print
void Poisson::print() const
{
    Etre::print();
    note("Je suis un poisson: " + to_string(this->i));
    m_réseauDeNeurones.print(true);
    /* show("Je suis vivant depuis",m_tempsDeVie); */
    show("Plus grand temps de vie",m_plusGrandTempsDeVie);
    /* show("nombre de victoires",m_nbVictoire); */
}

//////////////////////////////////////////////////////// PRIVATE
