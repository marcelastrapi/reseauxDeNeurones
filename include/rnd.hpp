#pragma once

#include <stdlib.h>
#include <ctime>
#include <sys/time.h>

#include <displayer.hpp>
using namespace displayer;

/*
TODO truc que je ne comprends pas, je ne peux enlever le inline sur les
fonctions ou ça comme une erreur de linkage, alors que normalement, il n'y a pas
de fonction inline....
*/

namespace Rnd {
    typedef float rndType;

    inline void randomize() 
    {
        struct timeval t1;
        gettimeofday(&t1, nullptr );
        srand(static_cast<unsigned int>(t1.tv_usec * t1.tv_sec));
    }
    inline void randomize(unsigned int seed) 
    {
        srand(seed);
    }

    /*
       \brief template rnd(low,high)
       high NON inclue
       donc rnd(0,2) pour des int entre 0 et 1
       */
    template <class T>
    inline T rnd(rndType low = 0,rndType high = 1)
    {
        bool negatif(false);
        rndType diffTo0(0);

        if (low < 0)
        {
            // si c'est négatif alors je rend tout le monde positif
            negatif = true;
            diffTo0 = low * -1;
            low  += diffTo0;
            high += diffTo0;
        }

        rndType rndEntre0et1 = static_cast<rndType>(rand()) / static_cast<rndType>(RAND_MAX);
        T rep = static_cast<T>( rndEntre0et1 * (high-low) - low );

        if (negatif) rep -= static_cast<T>(diffTo0); 

        return rep;
    }

    inline bool _bool() 
    {
        return rand() % 2;
    }

    inline int _int(int max)  // entre 0 et max
    {
        return rand() % (max + 1);
    }
    inline int _int(int min, int max)
    {
        return min + rand() % (max + 1 - min) ;
    }

    inline double _double() // entre 0 et 1
    {
        return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    }
    inline double _double(double a, double b) // entre a et b (où a >= 0 et b < 1)
    {
        return static_cast<double>( a + rand() / (static_cast<double>(RAND_MAX) - (b+a) ));
    }
};
