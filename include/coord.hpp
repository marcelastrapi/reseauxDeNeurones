#pragma once

#include <string>
#include <displayer.hpp>

class Coord {
    public:
        float x;
        float y;
        Coord() { x = 0; y = 0; }
        Coord(float _x, float _y): x(_x), y(_y) {}
        Coord(const Coord &copy)
        {
            this->x = copy.x;
            this->y = copy.y;
        }

        inline std::string toString() const // TODO supprimer print
        {
            return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
        }
        inline void print() const
        {
            displayer::note("coord:"+toString());
        }

};


