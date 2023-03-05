#include <reseauDeNeurones.hpp>

RéseauDeNeurones::RéseauDeNeurones():
    m_input(1),m_output(1)
{ }

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
    nbHiddenLayers(réseauÀCopier.hiddenLayers().size());
    for (LigneDeNeurones& hiddenLayer: m_hiddenLayers)
        hiddenLayer = réseauÀCopier.hiddenLayers().at(i++);

    connecteLesLignesEntreElles();
}

RéseauDeNeurones::~RéseauDeNeurones() { }

// operators
bool RéseauDeNeurones::operator==(const RéseauDeNeurones& otherRes) const
{
    if (m_input.size() != otherRes.m_input.size())
        return false;

    if (m_hiddenLayers.size() != otherRes.m_hiddenLayers.size())
        return false;

    if (m_output.size() != otherRes.m_output.size())
        return false;

    // je regarde si chaque hiddenLayer est égal à l'autre
    for (size_t i = 0; i < m_hiddenLayers.size(); i++) {
        /* this->m_hiddenLayers.at(i) */
        if (m_hiddenLayers.at(i).size() != otherRes.m_hiddenLayers.at(i).size())
            return false;

        for (size_t j = 0; j < m_hiddenLayers.at(i).size(); j++) {
            if (m_hiddenLayers.at(i).at(j) != otherRes.m_hiddenLayers.at(i).at(j))
                return false;
        }
    }

    return true;
}

// setters
// TODO big bug, ne marche pas du tout si à l'init on a mis un certains
// nombre de neurones, il ne modifie que le dernier ?
void RéseauDeNeurones::nbHiddenLayers(const size_t nbHiddenLayers, const size_t nbNeurones)
{
    auto currentNbHiddenLayers = m_hiddenLayers.size();
    if (currentNbHiddenLayers >= nbHiddenLayers)
    {
        LignesDeNeurones::iterator it = m_hiddenLayers.begin();
        std::advance(it,nbHiddenLayers);
        // alors je dois supprimer des hiddenLayers
        m_hiddenLayers.erase(it , m_hiddenLayers.end());
    }
    else
    {
        // là je dois ajouter des hiddenLayers
        for (size_t i = currentNbHiddenLayers; i < nbHiddenLayers; i++)
            ajouteUnHiddenLayer(nbNeurones);
    }
    connecteLesLignesEntreElles();
}

void RéseauDeNeurones::poidsAléa(const nbType min, const nbType max)
{
    for (Neurone& n: m_input) n.poidsAléa(min,max);
    for (LigneDeNeurones& hiddenLayer: m_hiddenLayers)
        for (Neurone& n : hiddenLayer) n.poidsAléa(min,max);
    for (Neurone& n: m_output) n.poidsAléa(min,max);
}
void RéseauDeNeurones::poidsAléa(const nbType fourchetteAutourDuPoids)
{
    for (Neurone& n: m_input) n.poidsAléa(fourchetteAutourDuPoids);
    for (LigneDeNeurones& hiddenLayer: m_hiddenLayers)
        for (Neurone& n : hiddenLayer) n.poidsAléa(fourchetteAutourDuPoids);
    for (Neurone& n: m_output) n.poidsAléa(fourchetteAutourDuPoids);
}
void RéseauDeNeurones::seuil(const nbType _seuil)
{
    for (Neurone& n: m_input) n.seuil(_seuil);
    for (LigneDeNeurones& hiddenLayer: m_hiddenLayers)
        for (Neurone& n : hiddenLayer) n.seuil(_seuil);
    for (Neurone& n: m_output) n.seuil(_seuil);
}

void RéseauDeNeurones::tableauxDesValeursEnEntrée(const TblValeurs& _tblVals)
{
    size_t i = 0;
    for (const auto& val: _tblVals)
        m_input.at(i++).valeur(val);
}

// getters
RéseauDeNeurones::TblValeurs RéseauDeNeurones::tableauxDesRésultats() const
{
    TblValeurs rep;
    for (const Neurone& n: m_output)
        rep.emplace_back(n.valeur());
    return rep;
}

// sub
void RéseauDeNeurones::print(bool tout) const
{
    note ("Réseau de Neurones");
    show("input",m_input.size());
    show("hidden layers",m_hiddenLayers.size());
    show("output",m_output.size());
    if (nbHiddenLayers() > 0) {
        note("nbNeurones par hiddenLayers");
        for (const LigneDeNeurones& ligne: m_hiddenLayers)
            show("nbNeurones",ligne.size());
    }

    if (tout)
    {
        note("\n\t\t|| INPUT ||\n");
        for (const Neurone& n: m_input) n.print();
        note("\n\t\t|| HIDDEN LAYERS ||\n");
        for (const LigneDeNeurones& hiddenLayer: m_hiddenLayers)
        {
            note("\n\t\t\t|| HIDDEN LAYER ||\n");
            for (const Neurone& n: hiddenLayer) n.print();
        }
        note("\n\t\t|| OUTPUT ||\n");
        for (const Neurone& n: m_output) n.print();
    }
}

void RéseauDeNeurones::ajouteUnHiddenLayer(const size_t nbNeurones){
    m_hiddenLayers.emplace_back(LigneDeNeurones(nbNeurones));
}

void RéseauDeNeurones::connecteLesLignesEntreElles()
{
    if (nbHiddenLayers() > 0)
    {
        Neurone::CONNECTE_NEURONES_À_NEURONES(m_input,m_hiddenLayers.at(0));

        LignesDeNeurones::iterator it = m_hiddenLayers.begin();
        std::advance(it,1);
        for (size_t i = 0; i < nbHiddenLayers() - 1; i++)
            Neurone::CONNECTE_NEURONES_À_NEURONES(m_hiddenLayers.at(i),m_hiddenLayers.at(i+1));

        Neurone::CONNECTE_NEURONES_À_NEURONES(m_hiddenLayers.at(nbHiddenLayers()-1),m_output);
    }
    else
        Neurone::CONNECTE_NEURONES_À_NEURONES(m_input,m_output);

}

void RéseauDeNeurones::calculeLesValeursDeToutMesNeurones()
{
    for (LigneDeNeurones& hiddenLayer: m_hiddenLayers)
        for (Neurone& n: hiddenLayer)
            n.calculeMaValeurEnFonctionDesMesConnexions();

    for (Neurone& n: m_output)
        n.calculeMaValeurEnFonctionDesMesConnexions();
}
