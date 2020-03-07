#pragma once

#include <string>

class Couleur
{
    public:
        typedef unsigned char clType;
        unsigned char r; 
        unsigned char g; 
        unsigned char b; 
        unsigned char a; 

        // Ctor
        Couleur(): r(0),g(0),b(0),a(255) { }

        Couleur(clType _r, clType _g, clType _b, clType _a = 255):
            r(_r),g(_g),b(_b),a(_a) { }

        Couleur(const Couleur& clACopier) 
        {
            this->r = clACopier.r;
            this->g = clACopier.g;
            this->b = clACopier.b;
            this->a = clACopier.a;
        } 

        // Fonctions
        string toString() const
        {
            return to_string(static_cast<int>(r)) + "," + to_string(static_cast<int>(g)) + "," + to_string(static_cast<int>(b)) + "," + to_string(static_cast<int>(a));
        }
};

