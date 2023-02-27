#pragma once
#include <etre.hpp>

#include <displayer.hpp>
using namespace displayer;

#include <array>
using std::array;

/* \brief class Poisson
   un petit poisson
*/
class Poisson: public Etre
{
    public:
        const ESPECE espece = POISSON;
        Poisson();

        /* bool operator< (const Poisson &other) const { */
        /*     return this->m_plusGrandTempsDeVie < other.m_plusGrandTempsDeVie; */
        /* } */

        // print
        void print() const override;

        // sub
        void calculeNouvelleAngle(const nbType directionRequin);

        void renaît() override;

        // setters
        inline void plusGrandTempsDeVie(const Tic pgtdv) { m_plusGrandTempsDeVie = pgtdv; }

        // getters
        Tic plusGrandTempsDeVie() const { return m_plusGrandTempsDeVie; }

        int i; // TODO à virer mais pratique parfois

    private:
        // déclariation
        Tic m_plusGrandTempsDeVie;

};

