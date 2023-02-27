#pragma once

#include <neurone.hpp>

#include <vector>

class RéseauDeNeurones
{

    public:
        using Neurones = Neurone::Neurones;
        using LigneDeNeurones = Neurone::Neurones;
        using LignesDeNeurones = std::vector<Neurones>;
        using TblValeurs = std::vector<nbType>;
        //TODO il faudrait probablement un pointeur intelligent pour ne pas avoir à recopier tout le temps le tableau dans tableauxDesRésultats()

        RéseauDeNeurones();
        RéseauDeNeurones(
                const size_t _nbNeuronesInput,
                const size_t _nbHiddenLayers,
                const size_t _nbNeuronesHiddenLayers,
                const size_t _nbNeuronesOutput);
        RéseauDeNeurones(RéseauDeNeurones& réseauÀCopier);
        ~RéseauDeNeurones();

        // setters
        inline void nbNeuronesInput(const size_t nbNeurones){ m_input.resize(nbNeurones) ;}
        void nbHiddenLayers(const size_t nbHiddenLayers, const size_t nbNeurones = 4);
        inline void nbNeuronesOutput(const size_t nbNeurones){ m_output.resize(nbNeurones);}

        void poidsAléa(const nbType min, const nbType max);
        void poidsAléa(const nbType fourchetteAutourDuPoids);
        void seuil(const nbType _seuil);
        void tableauxDesValeursEnEntrée(const TblValeurs& _tblVals);

        // getters
        LigneDeNeurones& input() { return m_input; }
        LignesDeNeurones& hiddenLayers() { return m_hiddenLayers; }
        LigneDeNeurones& output() { return m_output; }
        TblValeurs tableauxDesRésultats() const;

        inline size_t nbHiddenLayers() const { return m_hiddenLayers.size(); }

        // sub
        void ajouteUnHiddenLayer(const size_t nbNeurones = 4);
        void connecteLesLignesEntreElles();
        void calculeLesValeursDeToutMesNeurones();


        void print(bool tout = false) const;

    private:
        LigneDeNeurones m_input;
        LignesDeNeurones m_hiddenLayers;
        LigneDeNeurones m_output;

};
