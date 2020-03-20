#include <reseauDeNeurones.hpp>

RéseauDeNeurones::RéseauDeNeurones():
    m_input(1),m_output(1)
{
    /* connecteLesLignesEntreElles(); */
}

RéseauDeNeurones::RéseauDeNeurones(const size_t _nbNeuronesInput, 
                const size_t _nbHiddenLayers, 
                const size_t _nbNeuronesHiddenLayers,
                const size_t _nbNeuronesOutput):
    m_input(_nbNeuronesInput),m_output(_nbNeuronesOutput)
{
    nbHiddenLayers(_nbHiddenLayers,_nbNeuronesHiddenLayers);
    connecteLesLignesEntreElles();
}

RéseauDeNeurones::RéseauDeNeurones(RéseauDeNeurones& réseauÀCopier):
    m_input(réseauÀCopier.input()),
    m_output(réseauÀCopier.output())
{
    size_t i(0);
    for (LigneDeNeurones* hiddenLayer: m_hiddenLayers)
        *hiddenLayer = *réseauÀCopier.hiddenLayers().at(i++);

    connecteLesLignesEntreElles();
}

RéseauDeNeurones::~RéseauDeNeurones()
{
    for (LigneDeNeurones* ligne: m_hiddenLayers)
        delete ligne;
}

// setters
void RéseauDeNeurones::nbHiddenLayers(const size_t nbHiddenLayers, const size_t nbNeurones)
{
    auto currentNbHiddenLayers = m_hiddenLayers.size();
    if (currentNbHiddenLayers >= nbHiddenLayers)
    {

        LignesDeNeurones::iterator it = m_hiddenLayers.begin();
        std::advance(it,nbHiddenLayers);
        // alors je dois supprimer des hiddenLayers
        // TODO est-ce que les pointeurs vers les neurones sont ici bien delete?
        m_hiddenLayers.erase(it , m_hiddenLayers.end());
    }
    else
    {
        // là je dois ajouter des hiddenLayers
        for (size_t i = currentNbHiddenLayers; i < nbHiddenLayers; i++)
            ajouteUnHiddenLayer(nbNeurones);
    }

}

void RéseauDeNeurones::poidsAléa(const nbType min, const nbType max)
{
    m_output.poidsAléa(min,max);
    for (LigneDeNeurones* hiddenLayer: m_hiddenLayers)
        hiddenLayer->poidsAléa(min,max);
    m_output.poidsAléa(min,max);
}
void RéseauDeNeurones::poidsAléa(const nbType fourchetteAutourDuPoids)
{
    m_output.poidsAléa(fourchetteAutourDuPoids);
    m_input.poidsAléa(fourchetteAutourDuPoids);
    for (LigneDeNeurones* hiddenLayer: m_hiddenLayers)
        hiddenLayer->poidsAléa(fourchetteAutourDuPoids);
}
void RéseauDeNeurones::seuil(const nbType _seuil)
{
    m_input.seuil(_seuil);
    for (LigneDeNeurones* hiddenLayer: m_hiddenLayers)
        hiddenLayer->seuil(_seuil);
    m_output.seuil(_seuil);
}

void RéseauDeNeurones::tableauxDesValeursEnEntrée(const TblValeurs& _tblVals)
{
    size_t i = 0;
    for (const auto& val: _tblVals)
        m_input.at(i++)->valeur(val);
}

// sub
void RéseauDeNeurones::print(bool tout) const
{
    note ("Réseau de Neurones");
    show("input",m_input.nbNeurones());
    show("hidden layers",m_hiddenLayers.size());
    show("output",m_output.nbNeurones());
    note("nbNeurones par hiddenLayers");
    for (LigneDeNeurones* ligne: m_hiddenLayers)
        show("nbNeurones",ligne->nbNeurones());

    if (tout)
    {
        m_input.print();
        for (LigneDeNeurones* hiddenLayer: m_hiddenLayers)
            hiddenLayer->print();
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
