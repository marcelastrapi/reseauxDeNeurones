#pragma once

#include <ligneDeNeurones.hpp>

#include <vector>

class RéseauDeNeurones
{

    public:
        using LignesDeNeurones = std::vector<LigneDeNeurones*>;
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
        inline void nbNeuronesInput(const size_t nbNeurones){ m_input.nbNeurones(nbNeurones) ;}
        inline void nbNeuronesOutput(const size_t nbNeurones){ m_output.nbNeurones(nbNeurones);}
        void nbHiddenLayers(const size_t nbHiddenLayers, const size_t nbNeurones = 4);
        void poidsAléa(const nbType min, const nbType max);
        void poidsAléa(const nbType fourchetteAutourDuPoids);
        void seuil(const nbType _seuil);
        void tableauxDesValeursEnEntrée(const TblValeurs& _tblVals);

        // getters
        inline LigneDeNeurones& input() { return m_input; }
        inline LignesDeNeurones& hiddenLayers() { return m_hiddenLayers; }
        inline LigneDeNeurones& output() { return m_output; }
        inline TblValeurs tableauxDesRésultats() const { return m_output.tableauxDesRésultats(); }
        
        inline size_t nbHiddenLayers() { return m_hiddenLayers.size(); }

        // sub
        inline void ajouteUnHiddenLayer(const size_t nbNeurones = 4) { m_hiddenLayers.push_back(new LigneDeNeurones(nbNeurones)); }
        void connecteLesLignesEntreElles();
        void calculeLesValeursDeToutMesNeurones();


        void print(bool tout = false) const;

    private:
        LigneDeNeurones m_input;
        LignesDeNeurones m_hiddenLayers;
        LigneDeNeurones m_output;

        // private sub
        void effaceToutesLesConnections();
};
