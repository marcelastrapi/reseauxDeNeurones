#include <requin.hpp>

#include <utils.hpp>

// Ctor
Requin::Requin(): m_nbCiblesMangées(0)
{
    m_forme = Cercle;
    m_maxDistanceDeDeplacement = 10;
}

//debug
void Requin::debug() const
{
    Etre::debug();
    note("Je suis un requin");
}

//sub
void Requin::ajouteCible(Etre* nouvelleCible)
{
    m_cibles.ajouteEtre(nouvelleCible);
}

void Requin::avance(Etre::nbType distanceDeDeplacement)
{
    Etre::avance(distanceDeDeplacement);
}



//////////////////////////////////////////////////////////// PRIVATE

// Chasse
void Requin::detectLaCibleLaPlusProche()
{
    float minDist = this->m_largeurDuMonde;
    float distance = 0;
    Etre* candidat;
    Etre* tmp;

    for (size_t i=0; i < getNbCibles(); i++)
    {
        tmp = m_cibles.getEtreNo(i);
        distance = dist(tmp->getPos(), m_pos);
        // Si je vois que la distance la cible //TODO faudrait que ce soit plus précis
        // est assez petite ... alors MANGE-LE
        if (distance < tmp->getLargeur()) {
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
    m_cibleLaPlusProche->setCouleur(255,255,0);
}

void Requin::mange(Etre* etre)
{
    m_nbCiblesMangées++ ;
    etre->reborn();
}

void Requin::prendLaDirectionDeLaCibleLaPlusProche()
{
    detectLaCibleLaPlusProche();
    auto nouvelleAngle = getAngleEntreMoiEt( m_cibleLaPlusProche );
    /* show("nouvelleAngle",nouvelleAngle); */
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
    this->setAngle(nouvelleAngle);
    /* show("Nouvelle angle pour requin",m_angle); */
}
