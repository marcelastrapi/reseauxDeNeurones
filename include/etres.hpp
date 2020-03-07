#pragma once

#include <vector>
using std::vector;
#include <etre.hpp>

/// \brief conteneur d' Etre
class Etres
{
    public:
        Etres();
        ~Etres();

        void ajouteEtre(Etre* nouvelleEtre);

        // getters
        inline vector<Etre*>& getEtres() { return this->m_etres; }
        inline size_t getTotal() const { return m_etres.size(); }
        inline Etre* getEtreNo(const size_t i) const { return m_etres.at(i); }

    private:
        vector<Etre*> m_etres;
};
