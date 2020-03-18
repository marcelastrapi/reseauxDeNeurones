#include <ligneDeNeurones.hpp>

LigneDeNeurones::LigneDeNeurones(const size_t nbNeurones)
{

    for (size_t i = 0; i < nbNeurones; i++)
        ajouteUnNeurone();

}

LigneDeNeurones::~LigneDeNeurones()
{
    for (Neurone* n: m_neurones)
        delete n;
}

// setters
void LigneDeNeurones::nbNeurones(const size_t nbNeurones)
{
    auto currentNbNeurones = this->nbNeurones();
    if (currentNbNeurones >= nbNeurones)
    {

        iterator it = m_neurones.begin();
        std::advance(it,nbNeurones);
        // alors je dois supprimer des neurones
        m_neurones.erase(it , m_neurones.end());
    }
    else
    {
        // là je dois ajouter des neurones
        for (size_t i = currentNbNeurones; i < nbNeurones; i++)
            ajouteUnNeurone();
    }

}

// getters
LigneDeNeurones::TblRésultats LigneDeNeurones::tableauxDesRésultats() const
{
    TblRésultats rep;
    for (const Neurone* n: m_neurones)
        rep.push_back(n->valeur());

    return rep;
}

// sub
// moi vers autre ligne (donc de gauche à droite)
void LigneDeNeurones::connecteMoiÀUneAutreLigne(LigneDeNeurones& autreLigne)
{
    for (Neurone* n: autreLigne)
        for (Neurone* m_n: m_neurones)
            n->connecteMoiÀUnAutreNeurone(m_n);
}
void LigneDeNeurones::calculeLesValeursDeToutMesNeurones()
{
    for (Neurone* n: m_neurones)
        n->calculeMaValeurEnFonctionDesMesConnections();
}
void LigneDeNeurones::print() const
{
    note("_ Je suis une Ligne De Neurones ______________________________");
    show("  Nombre de neurones",m_neurones.size());
    note("______ Je print mes neurones");
    for (Neurone* n: m_neurones)
        n->print();

}
