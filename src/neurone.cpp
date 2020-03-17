#include <neurone.hpp>

Neurone::Neurone():
    m_poids(0),
    m_valeur(0),
    m_min(0)
{
    setPoidsAléa();
}

// setters
void Neurone::setPoidsAléa(const nbType min, const nbType max)
{
    m_poids = Rnd::rnd(min,max);
}

// getters

// sub
void Neurone::connecteMoiÀUnAutreNeurone(Neurone* neurone)
{
    this->m_neuronesConnectés.push_back(neurone);
}
void Neurone::print() const
{
    note("__ Je suis un Neurone _");
    show("nombre de connexion",this->getNbConnexions());
    show("poids",m_poids);
    show("valeurs",m_valeur);
}

// functions
nbType Neurone::calculeMaValeurEnFonctionDesMesConnections()
{
    // Je dois donc ajouter tout les produits poids*valeurs des mes neurones
    // connectés
    m_valeur = 0;
    for (const Neurone* n: m_neuronesConnectés)
        m_valeur += n->getPoids() * n->getValeur();

    // ce produit passer par la fonction max(0,x) sera ma valeur
    m_valeur = max(m_min,m_valeur);

    return m_valeur;
}
