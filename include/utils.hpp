#pragma once

#include <coord.hpp>
#include <cmath> // pour pow()

// ------- fonctions utile qu'ici ---------
template <class T>
inline T min(T a, T b){
	return (a<b)?a:b;
}

template <class T>
inline T max(T a, T b){
	return (a>b)?a:b;
}

template <class T>
T dist(T a,T b){
	return (max(a,b) - min(a,b));
}

inline float dist(const Coord& a, const Coord& b)
{
    return sqrtf(powf(dist(a.x,b.x),2) + powf(dist(a.y,b.y),2));
}

inline float radToDeg(const float angle)
{
    // deg * 180/PI = rad
    return angle * static_cast<float>(static_cast<double>(180.f)/3.141592653589793238463);
}
inline float degToRad(const float angle)
{
    return angle * static_cast<float>(3.141592653589793238463/180);
}


// Pour le temps
#include <chrono>

inline long getEpochNow()
{
    using namespace std::chrono;

    auto now = system_clock::now();
    auto now_ms = time_point_cast<milliseconds>(now);

    auto value = now_ms.time_since_epoch();

    return value.count();

}

/* inline std::string millisecondsToString(const milliseconds& ms) */
/* { */
/*     return "nan mais nan..."; */
/* } */
