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
        Etre* m_requin; // pour avoir sa pos en tps réel
        static const ESPECE espece = POISSON;
        Poisson();

        // debug
        void debug() const override;

        // sub
        void calculeNouvelleAngle();
        // override
        void reborn() override;

        // setters
        inline void setRequin(Etre* requin) { m_requin = requin; }

    private:
        // déclariation
        array<nbType,2> m_variablesAléatoires;

        // aléa
        nbType m_minRnd;
        nbType m_maxRnd;

        // sub
        void initialiseLesVariablesAléatoires();


};

