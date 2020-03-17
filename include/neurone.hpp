#pragma once

#include <vector>

#include <utils.hpp>

typedef float nbType;

class Neurone
{
    public:
        Neurone();
        
        // setters

        // getters
        inline nbType getPoids() const { return m_poids; }
        inline nbType getValeur() const { return m_valeur; }

        // sub
        void ajouteMoiUneConnexionVersUnNeurone(Neurone* neurone);
        void calculeMaValeurEnFonctionDesMesConnections();

        // functions

    private:
        nbType m_poids;
        nbType m_valeur;
        nbType m_min;
        // vector de pointeur vers les neurons qui sont connecté à mois
        std::vector<Neurone*> m_neuronesConnectés;


};
