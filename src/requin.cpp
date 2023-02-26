#include <requin.hpp>

#include <utils.hpp>

// Ctor
Requin::Requin():
    m_nbCiblesMangées(0),
    m_icibleEnCours(0)
{
    m_estMouvant = true;
    m_estVivant = true;
    m_forme = Cercle;
    m_maxDistanceDeDeplacement = 10;
}

//print
void Requin::print() const
{
    Etre::print();
    note("Je suis un requin");
}

// override
void Requin::renaît()
{
    /* m_nbCiblesMangées = 0; */
    /* Etre::renaît(); */
}

//////////////////////////////////////////////////////////// PRIVATE

// Chasse
void Requin::detectLaCibleLaPlusProche()
{
    float minDist = sqrt(pow(2,this->m_largeurDuMonde) + pow(2, this->m_hauteurDuMonde));
    float distance = 0;
    Etre* candidat;
    Etre* tmp;

    for (size_t i=0; i < nbCibles(); i++)
    {
        tmp = m_cibles.at(i);
        distance = dist(tmp->pos(), m_pos);
        // Si je vois que la distance la cible //TODO faudrait que ce soit plus précis
        // est assez petite ... alors MANGE-LE
        if (distance < tmp->rayon() + this->rayon()) {
            this->mange(tmp);
            continue;
        }
        if ( distance < minDist ) {
            minDist = distance;
            candidat = tmp;
        }

    }
    m_minDistDeLaCibleLaPlusProche = minDist;
    m_cibleLaPlusProche = candidat;
}

void Requin::mange(Etre* etre)
{
    m_nbCiblesMangées++ ;
    etre->renaît();
}

void Requin::prendLaDirectionDeLaCibleLaPlusProche()
{
    detectLaCibleLaPlusProche();

    auto nouvelleAngle = getAngleEntreMoiEt( m_cibleLaPlusProche );
    this->angleDeDirection(nouvelleAngle);
}
