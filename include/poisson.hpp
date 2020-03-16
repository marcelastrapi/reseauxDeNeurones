#pragma once
#include <etre.hpp>

#include <displayer.hpp>
using namespace displayer;

#include <array>
using std::array;

#include <cmath>
#include <utils.hpp>

/* \brief class Poisson
   un petit poisson
*/
class Poisson: public Etre
{
    public:
        static const ESPECE espece = POISSON;
        static const size_t NB_TPS_DE_VIE = 10;
        Poisson();

        // debug
        void debug() const override;

        // sub
        void calculeNouvelleAngle(const nbType directionRequin);

        void renaît() override;

        // setters

        long m_maxTempsDeVie;
        array<nbType,2> m_variablesAléatoires;
    private:
        // déclariation
        long m_epochNaissance;
        array<long,NB_TPS_DE_VIE> m_tempsDeVie;
        size_t m_iTempsDeVie;
        nbType m_valeursAAjouterAVarAléa;
        /* std::time_t m_oldTempsDeVie; */

        // aléa
        /* nbType m_minRnd; */
        /* nbType m_maxRnd; */

        // sub
    public: void initialiseLesVariablesAléatoires();


};

