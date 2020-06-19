#pragma once

#include <coord.hpp>
#include <etre.hpp>
#include <poisson.hpp>

class Monde
{
    public:
        Monde(unsigned int largeur = 1000, unsigned int hauteur = 1000);

        // Getters
        inline unsigned int largeur() const { return this->m_largeur; }
        inline unsigned int hauteur() const { return this->m_hauteur; }

        inline Etres& getToutLesEtres() { return this->m_toutLesEtres; }
        inline size_t getNbEtres() const { return this->m_toutLesEtres.size(); }
        inline Etre* at(unsigned int i) const { return m_toutLesEtres.at(i); }

        Tic ticDepuisCréation() const { return m_ticDepuisCréation; }

        // Setters
        inline void ajouteEtre(Etre* etre) { m_toutLesEtres.push_back(etre); }

        // Sub
        void tic();

        // Display
        void print() const {
            for (unsigned int i = 0; i < getNbEtres(); i++)
                m_toutLesEtres.at(i)->print();
        }

    private:
        // Déclarations
        unsigned int m_largeur;
        unsigned int m_hauteur;

        Tic m_ticDepuisCréation;

        // Tout qui est présent dans le monde
        // C'est un tableau de podoubleeurs vers des objets de la class mère Etre
        Etres m_toutLesEtres;


        Coord getRoundCoord(Etre::nbType x, Etre::nbType y);

};


