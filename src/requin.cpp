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

//sub
void Requin::ajouteCible(Etre* nouvelleCible)
{
    m_cibles.ajouteEtre(nouvelleCible);
}


//////////////////////////////////////////////////////////// PRIVATE

// Chasse
void Requin::detectLaCibleLaPlusProche()
{
    float minDist = this->m_largeurDuMonde;
    float distance = 0;
    Etre* candidat;
    Etre* tmp;

    for (size_t i=0; i < nbCibles(); i++)
    {
        tmp = m_cibles.getEtreNo(i);
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
    /* show("m_angle",m_angle); */
    /* show("dist(nouvelleAngle,m_angle)",dist(nouvelleAngle,m_angle)); */
    /* auto distEntreLes2Angles = dist(nouvelleAngle,m_angle); */
    /* if (distEntreLes2Angles > m_maxAngleDeRotation) */
    /* { */
    /*     if (nouvelleAngle > m_angle) */
    /*         nouvelleAngle = m_angle + m_maxAngleDeRotation; */
    /*     else */
    /*         nouvelleAngle = m_angle - m_maxAngleDeRotation; */
    /* } */
    /* show("nouvelleAngle",nouvelleAngle); */
    this->angleDeDirection(nouvelleAngle);
    /* show("Nouvelle angle pour requin",m_angle); */
}
