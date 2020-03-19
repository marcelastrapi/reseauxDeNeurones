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

        // print
        void print() const override;

        // sub
        void calculeNouvelleAngle(const nbType directionRequin);

        void renaît() override;

        // setters

    private:
        // déclariation

};

