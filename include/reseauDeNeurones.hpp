#pragma once

#include <ligneDeNeurones.hpp>

#include <vector>

class RéseauDeNeurones
{

    public:
        using LignesDeNeurones = std::vector<LigneDeNeurones*>;
        using TblRésultats = std::vector<nbType>;

        RéseauDeNeurones();
        ~RéseauDeNeurones();

        // setters
        inline void nbNeuronesInput(const size_t nbNeurones){ m_input.nbNeurones(nbNeurones) ;}
        inline void nbNeuronesOuput(const size_t nbNeurones){ m_output.nbNeurones(nbNeurones);}
        void nbHiddenLayers(const size_t nbHiddenLayers);
        void poidsAléa(const nbType min = 0, const nbType max = 1);

        // getters
        inline LigneDeNeurones& input() { return m_input; }
        inline LignesDeNeurones& hiddenLayers() { return m_hiddenLayers; }
        inline LigneDeNeurones& output() { return m_output; }
        inline TblRésultats tableauxDesRésultats() const { return m_output.tableauxDesRésultats(); }
        
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
