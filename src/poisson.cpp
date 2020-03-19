#include <poisson.hpp>

Poisson::Poisson(): m_plusGrandTempsDeVie(0)
{
    m_estMouvant = true;
    m_estVivant = true;
    m_forme = Cercle;

    // RéseauDeNeurones 
    m_réseauDeNeurones.nbNeuronesInput(1);
    m_réseauDeNeurones.nbHiddenLayers(2,8);
    m_réseauDeNeurones.nbNeuronesOuput(1);
    m_réseauDeNeurones.connecteLesLignesEntreElles();

    m_réseauDeNeurones.poidsAléa(-3.14f,3.14f);
    /* m_réseauDeNeurones.output().poidsAléa(0,1); */
    m_réseauDeNeurones.output().at(0)->seuil(-500);
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
    note("Je suis un poisson");
    show("Je suis vivant depuis",m_tempsDeVie);
}

//////////////////////////////////////////////////////// PRIVATE
