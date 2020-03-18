#pragma once

#include <vector>

#include <utils.hpp>
#include <displayer.hpp>
using namespace displayer;

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

        // Pour pouvoir faire comme dans un vector (itérer)
        iterator begin() { return m_neuronesConnectés.begin(); }
        iterator end() { return m_neuronesConnectés.end(); }
        const_iterator begin() const { return m_neuronesConnectés.begin(); }
        const_iterator end() const { return m_neuronesConnectés.end(); }
        const_iterator cbegin() const { return m_neuronesConnectés.cbegin(); }
        const_iterator cend() const { return m_neuronesConnectés.cend(); }

        // setters
        void poidsAléa(const nbType min = 0, const nbType max = 1);
        inline void poids(const nbType poids) { m_poids = poids; }
        inline void valeur(const nbType valeur) { m_valeur = valeur; }

        // getters
        inline nbType poids() const { return m_poids; }
        inline nbType valeur() const { return m_valeur; }
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
