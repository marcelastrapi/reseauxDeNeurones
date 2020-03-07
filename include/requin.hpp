#pragma once

#include <etre.hpp>
#include <etres.hpp>

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

        // getters
        inline size_t getNbCibles() const { return m_cibles.getTotal(); }

        // debug
        void debug() const;

        // sub
        void ajouteCible(Etre* nouvelleCible);
        void avance(Etre::nbType distanceDeDeplacement);

        Etre::nbType m_minDistDeLaCibleLaPlusProche;
        Etre* m_cibleLaPlusProche;

    private:
        Etres m_cibles;

        // Chasse
        void mange(Etre* etre);
        void detectLaCibleLaPlusProche() ;

    public: void prendLaDirectionDeLaCibleLaPlusProche();

};
