#include <etres.hpp>


// Ctor & Dtor
Etres::Etres() {}

Etres::~Etres() 
{
    for (auto e: m_etres)
        delete e;
}

// sub
void Etres::ajouteEtre(Etre* nouvelleEtre)
{
    this->m_etres.push_back(nouvelleEtre);
}

// setters
