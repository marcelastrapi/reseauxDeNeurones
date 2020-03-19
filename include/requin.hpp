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
        inline void nbCiblesMangées(const unsigned int _nbCiblesMangée) { m_nbCiblesMangées = _nbCiblesMangée; }

        // getters
        inline size_t nbCibles() const { return m_cibles.getTotal(); }
        inline unsigned int nbCiblesMangées() const { return m_nbCiblesMangées; }

        Etre* prochaineCible() 
        {
            Etre* cibleEnCours = m_cibles.getEtreNo(m_icibleEnCours);
            auto distance = dist(cibleEnCours->pos(), m_pos);

            if (distance <= cibleEnCours->rayon() + rayon())
            {
                mange(cibleEnCours);
                /* note("J'ai enfin bouffer:"); */
                /* cibleEnCours->print(); */

                m_icibleEnCours = (m_icibleEnCours + 1)% m_cibles.getTotal();
            }

            /* note("prochaineCible"); */
            /* m_cibles.getEtreNo(m_icibleEnCours)->print(); */
            return m_cibles.getEtreNo(m_icibleEnCours);
        }

        // print
        void print() const;

        // sub
        void ajouteCible(Etre* nouvelleCible);
        inline void avance() { Etre::avance(); }

        Etre::nbType m_minDistDeLaCibleLaPlusProche;
        Etre* m_cibleLaPlusProche;

    private:
        Etres m_cibles;
        unsigned int m_nbCiblesMangées;
        size_t m_icibleEnCours;

        // Chasse
        void mange(Etre* etre);
        void detectLaCibleLaPlusProche() ;

    public: void prendLaDirectionDeLaCibleLaPlusProche();

};
