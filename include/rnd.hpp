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
       donc rnd<int>(0,2) pour des int entre 0 et 1
       */
    /* template <class T> */
    /* inline T rnd(rndType low = 0,rndType high = 1) */
    /* { */
    /*     rndType rndEntre0et1 = static_cast<double>(rand()) / static_cast<rndType>(RAND_MAX); */
    /*     return static_cast<T>( rndEntre0et1 * abs(high-low) + low ); */
    /* } */

    inline bool _bool()
    {
        return rand() % 2;
    }

    inline int _int(int max)  // entre 0 et max
    {
        return rand() % (max + 1);
    }
    // [min, max]
    inline int _int(int min, int max)
    {
        return min + (rand() % (max-min+1)) ;
    }

    // [0,1[
    inline float _float()
    {
        return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
    // entre [a,b] donc a et b exclut
    inline float _float(float a, float b)
    {
        return a + (rand()/(float)RAND_MAX * (b-a)) ;
    }

    // [0,1]
    inline double _double()
    {
        return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
    }
    // entre [a,b] donc a et b exclut
    inline double _double(double a, double b)
    {
        return a + (rand()/(double)RAND_MAX * (b-a)) ;
    }
};
