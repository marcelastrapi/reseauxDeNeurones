#pragma once

#include <vector>
using std::vector;
#include <etre.hpp>

/// \brief conteneur d' Etre
class Etres
{
    private:
        using Etres_t = std::vector<Etre*>;

    public:
        using iterator = Etres_t::iterator;
        using const_iterator = Etres_t::const_iterator;

        Etres();
        ~Etres();

        // Pour pouvoir faire comme dans un vector (itérer)
        iterator begin() { return m_etres.begin(); }
        iterator end() { return m_etres.end(); }
        const_iterator begin() const { return m_etres.begin(); }
        const_iterator end() const { return m_etres.end(); }
        const_iterator cbegin() const { return m_etres.cbegin(); }
        const_iterator cend() const { return m_etres.cend(); }

        void ajouteEtre(Etre* nouvelleEtre);

        // getters
        inline Etres_t& getEtres() { return this->m_etres; }
        inline size_t getTotal() const { return m_etres.size(); }
        inline Etre* getEtreNo(const size_t i) const { return m_etres.at(i); }

    private:
        Etres_t m_etres;
};
