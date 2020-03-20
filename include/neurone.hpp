#pragma once

#include <vector>

#include <utils.hpp>
/* #include <displayer.hpp> */
/* using namespace displayer; */

#include <rnd.hpp>

typedef float nbType;

class Neurone
{
    private:
        using Neurones = std::vector<Neurone*>;

    public:
        using iterator = Neurones::iterator;
        using const_iterator = Neurones::const_iterator;

        Neurone();
        Neurone(const Neurone& neuroneÀCopier);

        // Pour pouvoir faire comme dans un vector (itérer)
        iterator begin() { return m_neuronesConnectés.begin(); }
        iterator end() { return m_neuronesConnectés.end(); }
        const_iterator begin() const { return m_neuronesConnectés.begin(); }
        const_iterator end() const { return m_neuronesConnectés.end(); }
        const_iterator cbegin() const { return m_neuronesConnectés.cbegin(); }
        const_iterator cend() const { return m_neuronesConnectés.cend(); }

        // setters
        void poidsAléa(const nbType, const nbType max);
        void poidsAléa(const nbType fourchetteAutourDuPoids);
        inline void poids (const nbType _poids ) { m_poids  = _poids ; }
        inline void valeur(const nbType _valeur) { m_valeur = _valeur; }
        inline void seuil (const nbType _seuil ) { m_seuil  = _seuil ; }

        // getters
        inline nbType poids() const { return m_poids; }
        inline nbType valeur() const { return m_valeur; }
        inline nbType seuil() const { return m_seuil; }
        inline size_t nbConnexions() const { return m_neuronesConnectés.size(); }

        // sub
        void connecteMoiÀUnAutreNeurone(Neurone* neurone);
        void print() const;

        inline void effaceToutesLesConnections() { m_neuronesConnectés.clear(); }

        // functions
        nbType calculeMaValeurEnFonctionDesMesConnections();

    private:
        nbType m_poids;
        nbType m_valeur;
        nbType m_seuil;
        // vector de pointeur vers les neurones qui sont connecté à moi
        Neurones m_neuronesConnectés;

};
