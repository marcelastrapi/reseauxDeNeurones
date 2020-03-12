#pragma once

#include <displayer.hpp>
using namespace displayer;

#include <coord.hpp>
#include <rnd.hpp>
#include <couleur.hpp>

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
   // angle en radian
   //    0     va à droite
   //    PI/2  monte
   //    PI    va è gauche
   //   -PI/2  descend
*/
class Etre
{

    public:
        static const ESPECE espece = ETRE;
        typedef float nbType;
        typedef float angleType;

        Etre();
        virtual ~Etre() {}

        //debug
        virtual void debug() const = 0;

        // setters
        inline void setForme(const Forme forme) { m_forme = forme; }
        inline void setCouleur(const Couleur& cl) { m_couleur = cl; }
        inline void setCouleur(const Couleur::clType r, const Couleur::clType g, const Couleur::clType b, const Couleur::clType a=255) { setCouleur(Couleur(r,g,b,a)); }
        void setDimensionDuMonde(const nbType largeur, const nbType hauteur);
        // diametre | côté
        inline void setLargeur(const nbType largeur) { m_largeur = largeur; }
        inline void setHauteur(const nbType hauteur) { m_hauteur = hauteur; }
        void setDimension(const nbType largeur, const nbType hauteur);
        inline void setPos(const nbType x, const nbType y) { setLeft(x);setTop(y); }
        inline void setPos(const Coord& coord) { setPos(coord.x,coord.y); }
        // angle entre -1 et 1
        void setAngleDeRotation(const angleType angle);
        inline void setMouvant(const bool mouvant) { m_mouvant = mouvant; }
        inline void setMaxDistanceDeDeplacement(const nbType max) { m_maxDistanceDeDeplacement = max; }
        inline void setMaxAngleDeRotation(const nbType angleDeDirection) { m_maxAngleDeRotation = angleDeDirection; }

        void setLeft(const nbType left);
        void setTop (const nbType top);
        inline void setRight (const nbType right)  { setLeft(right - m_largeur); }
        inline void setBottom(const nbType bottom) { setTop (bottom - m_hauteur); }

        // getters
        inline Forme getForme() const { return m_forme; }
        inline nbType getMaxPosX() const { return m_largeurDuMonde; }
        inline nbType getMaxPosY() const { return m_hauteurDuMonde; }
        inline nbType getLargeur() const { return m_largeur; }
        inline nbType getHauteur() const { return m_hauteur; }
        inline Coord getPos() const { return m_pos; }
        inline Couleur& getCouleur() { return m_couleur; }
        inline angleType getAngle() const { return m_angleDeDirection; }
        inline bool getMouvant() const { return m_mouvant; }
        inline nbType getMaxDistanceDeDeplacement() const { return m_maxDistanceDeDeplacement; }

        inline nbType getLeft()   const { return m_pos.x            ; }
        inline nbType getTop()    const { return m_pos.y            ; }
        inline nbType getRight()  const { return m_pos.x + m_largeur; }
        inline nbType getBottom() const { return m_pos.y + m_hauteur; }

        // sub
        // l'être avance son angle de rotation et la distanceDeDeplacement/maxDistDepl
        void avance(nbType distanceDeDeplacement);
        inline void avance() { avance(m_maxDistanceDeDeplacement); }
        virtual void reborn();

        angleType getAngleEntreMoiEt(const Etre* lui) const;

    protected:
        Coord m_pos;
        Forme m_forme;
        Couleur m_couleur;
        nbType m_largeurDuMonde;
        nbType m_hauteurDuMonde;
        nbType m_largeur;
        nbType m_hauteur;
        angleType m_angleDeDirection;

        bool m_mouvant;
        angleType m_maxAngleDeRotation;
        nbType m_maxDistanceDeDeplacement;


};
