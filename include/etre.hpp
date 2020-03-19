#pragma once

#include <displayer.hpp>
using namespace displayer;

#include <coord.hpp>
#include <rnd.hpp>
#include <couleur.hpp>

#include <reseauDeNeurones.hpp>

enum Forme 
{
    Cercle,
    Rectangle
};

enum ESPECE
{
    ETRE,
    POISSON,
    REQUIN
};

/* \brief class Etre

   pos est un Coord au centre de l'être

   angle en radian
      0     va à droite
      PI/2  monte
      PI    va è gauche
     -PI/2  descend
   
   
*/

typedef long Tic;

class Etre
{

    public:
        static const ESPECE espece = ETRE;
        typedef float nbType;
        typedef float angleType;

        Etre();
        virtual ~Etre() {}

        //print
        virtual void print() const = 0;

        // setters
        inline void forme(const Forme forme) { m_forme = forme; }
        inline void couleur(const Couleur& cl) { m_couleur = cl; }
        inline void couleur(const Couleur::clType r, const Couleur::clType g, const Couleur::clType b, const Couleur::clType a=255) { couleur(Couleur(r,g,b,a)); }
        void dimensionDuMonde(const nbType largeur, const nbType hauteur);
        // diametre | côté
        void largeur(const nbType largeur);
        void hauteur(const nbType hauteur);
        void dimension(const nbType largeur, const nbType hauteur);
        inline void pos(const nbType x, const nbType y) { setLeft(x-m_largDiv);setTop(y-m_hautDiv); }
        inline void pos(const Coord& coord) { pos(coord.x,coord.y); }
        void posAléa();
        // angle entre 0 et 2pi
        void angleDeDirection(const angleType angle);
        inline void mouvant(const bool mouvant) { m_estMouvant = mouvant; }
        inline void maxDistanceDeDéplacement(const nbType max) { m_maxDistanceDeDeplacement = max; }
        inline void maxAngleDeDirection(const nbType angleDeDirection) { m_maxAngleDeDirection = angleDeDirection; }

        void setLeft(const nbType left);
        void setTop (const nbType top);
        inline void setRight (const nbType right)  { setLeft(right -  m_largeur); }
        inline void setBottom(const nbType bottom) { setTop (bottom - m_hauteur); }
        inline void estVivant(const bool vivant) { m_estVivant = vivant; }

        // getters
        Forme forme() const { return m_forme; }
        nbType maxPosX() const { return m_largeurDuMonde; }
        nbType maxPosY() const { return m_hauteurDuMonde; }
        nbType largeur() const { return m_largeur; }
        nbType hauteur() const { return m_hauteur; }
        nbType rayon() const { return m_largDiv; }
        Coord pos() const { return m_pos; }
        Couleur& couleur() { return m_couleur; }
        angleType angleDeDirection() const { return m_angleDeDirection; }
        bool mouvant() const { return m_estMouvant; }
        nbType maxDistanceDeDéplacement() const { return m_maxDistanceDeDeplacement; }
        bool estVivant() const { return m_estVivant; }
        Tic tempsDeVie() const { return m_tempsDeVie; }

        nbType getLeft()   const { return m_pos.x - m_largDiv ; }
        nbType getTop()    const { return m_pos.y - m_hautDiv ; }
        nbType getRight()  const { return m_pos.x + m_largDiv ; }
        nbType getBottom() const { return m_pos.y + m_hautDiv ; }

        // sub
        // l'être avance son angle de rotation et la distanceDeDeplacement/maxDistDepl
        void avance(nbType distanceDeDeplacement);
        inline void avance() { avance(m_maxDistanceDeDeplacement); }

        virtual void renaît();

        // ajoute 1 à m_tempsDeVie si m_estVivant et avance() si m_estMouvant
        void tic();

        angleType getAngleEntreMoiEt(const Etre* lui) const;

    protected:
        Coord m_pos;
        Forme m_forme;
        Couleur m_couleur;
        nbType m_largeurDuMonde;
        nbType m_hauteurDuMonde;
        nbType m_largeur;
        nbType m_hauteur;
        nbType m_largDiv;
        nbType m_hautDiv;

        bool m_estMouvant;
        nbType m_maxDistanceDeDeplacement;
        angleType m_angleDeDirection;
        angleType m_maxAngleDeDirection;

        bool m_estVivant;
        Tic m_tempsDeVie;

        RéseauDeNeurones m_réseauDeNeurones;

};
