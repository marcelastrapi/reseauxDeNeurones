#pragma once

#include <etre.hpp>
#include <etres.hpp>

#include <utils.hpp>

/*
   \\\brief class Requin
   c'est un requin qui doit connaitre toutes les positions des poissons
   et qui va aller manger celui qui est le plus proche de lui
*/
class Requin: public Etre
{
    public:
        static const ESPECE espece = REQUIN;
        Requin();

        // setters
        inline void setNbCiblesMangées(const unsigned int nbCiblesMangée) { m_nbCiblesMangées = nbCiblesMangée; }
        // getters
        inline size_t getNbCibles() const { return m_cibles.getTotal(); }
        inline unsigned int getNbCiblesMangées() const { return m_nbCiblesMangées; }

        Etre* getProchaineCible() {
            /* m_cibleEnCours = (m_cibleEnCours + 1)% m_cibles.getTotal(); */
            auto distance = dist(m_cibles.getEtreNo(m_cibleEnCours)->getPos(), m_pos);
            // Si je vois que la distance la cible //TODO faudrait que ce soit plus précis
            // est assez petite ... alors MANGE-LE

            if (distance < m_cibles.getEtreNo(m_cibleEnCours)->getRayon() + getRayon()) {
                mange(m_cibles.getEtreNo(m_cibleEnCours));
                m_cibleEnCours = (m_cibleEnCours + 1)% m_cibles.getTotal();
            }

            return m_cibles.getEtreNo(m_cibleEnCours);
        }

        // debug
        void debug() const;

        // sub
        void ajouteCible(Etre* nouvelleCible);
        void avance(Etre::nbType distanceDeDeplacement);
        inline void avance() { Etre::avance(); }

        Etre::nbType m_minDistDeLaCibleLaPlusProche;
        Etre* m_cibleLaPlusProche;

    private:
        Etres m_cibles;
        unsigned int m_nbCiblesMangées;
        size_t m_cibleEnCours;

        // Chasse
        void mange(Etre* etre);
        void detectLaCibleLaPlusProche() ;

    public: void prendLaDirectionDeLaCibleLaPlusProche();

};
