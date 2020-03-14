#pragma once
#include <etre.hpp>

#include <ctime>
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

        void renaît() override;

        // setters

        std::time_t m_maxTempsDeVie;
        array<nbType,2> m_variablesAléatoires;
    private:
        // déclariation
        std::time_t m_epochNaissance;
        /* std::time_t m_oldTempsDeVie; */

        // aléa
        nbType m_minRnd;
        nbType m_maxRnd;

        // sub
        void initialiseLesVariablesAléatoires();


};

