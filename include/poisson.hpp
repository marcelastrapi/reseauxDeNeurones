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
        static const ESPECE espece = POISSON;
        Poisson();

        // debug
        void debug() const override;

        // sub
        void calculeNouvelleAngle(const nbType directionRequin);

        void reborn() override;

        // setters

    private:
        // déclariation
        array<nbType,2> m_variablesAléatoires;

        // aléa
        nbType m_minRnd;
        nbType m_maxRnd;

        // sub
        void initialiseLesVariablesAléatoires();


};

