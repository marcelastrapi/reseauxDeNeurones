#include <reseauDeNeurones.hpp>

RéseauDeNeurones::RéseauDeNeurones():
    m_input(1),m_output(1)
{ }
RéseauDeNeurones::~RéseauDeNeurones()
{
    for (LigneDeNeurones* ligne: m_hiddenLayers)
        delete ligne;
}

// setters
void RéseauDeNeurones::nbHiddenLayers(const size_t nbHiddenLayers)
{
    auto currentNbHiddenLayers = m_hiddenLayers.size();
    if (currentNbHiddenLayers >= nbHiddenLayers)
    {

        LignesDeNeurones::iterator it = m_hiddenLayers.begin();
        std::advance(it,nbHiddenLayers);
        // alors je dois supprimer des neurones
        m_hiddenLayers.erase(it , m_hiddenLayers.end());
    }
    else
    {
        // là je dois ajouter des neurones
        for (size_t i = currentNbHiddenLayers; i < nbHiddenLayers; i++)
            ajouteUnHiddenLayer();
    }

}


// sub
void RéseauDeNeurones::print(bool tout) const
{
    note ("Réseau de Neurones");
    show("input",m_input.nbNeurones());
    show("hidden layers",m_hiddenLayers.size());
    show("ouput",m_output.nbNeurones());
    note("nbNeurones par hiddenLayers");
    for (LigneDeNeurones* ligne: m_hiddenLayers)
        show("nbNeurones",ligne->nbNeurones());

    if (tout)
    {
        m_input.print();
        for (LigneDeNeurones* ligne: m_hiddenLayers)
            ligne->print();
        m_output.print();
    }
}

void RéseauDeNeurones::connecteLesLignesEntreElles()
{
    effaceToutesLesConnections();

    if (nbHiddenLayers() > 0)
    {
        m_input.connecteMoiÀUneAutreLigne(*m_hiddenLayers.at(0));

        LignesDeNeurones::iterator it = m_hiddenLayers.begin();
        std::advance(it,1);
            for (size_t i = 0; i < nbHiddenLayers() - 1; i++)
            m_hiddenLayers.at(i)->connecteMoiÀUneAutreLigne(*m_hiddenLayers.at(i+1));

        m_hiddenLayers.at(nbHiddenLayers()-1)->connecteMoiÀUneAutreLigne(m_output);
    }
    else
        m_input.connecteMoiÀUneAutreLigne(m_output);

}

void RéseauDeNeurones::calculeLesValeursDeToutMesNeurones()
{
    for (LigneDeNeurones* hiddenLayer: m_hiddenLayers)
        hiddenLayer->calculeLesValeursDeToutMesNeurones();
    m_output.calculeLesValeursDeToutMesNeurones();
}

//////////////////////////////////////// PRIVATE
void RéseauDeNeurones::effaceToutesLesConnections()
{
    m_input.effaceToutesLesConnections();
    for (LigneDeNeurones* ligne: m_hiddenLayers)
        ligne->effaceToutesLesConnections();
    m_output.effaceToutesLesConnections();
}
