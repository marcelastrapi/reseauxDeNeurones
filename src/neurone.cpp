#include <neurone.hpp>

Neurone::Neurone():
    m_poids(0),
    m_valeur(0),
    m_min(0)
{ }

// getters

// sub
void Neurone::ajouteMoiUneConnexionVersUnNeurone(Neurone* neurone)
{
    this->m_neuronesConnectés.push_back(neurone);
}
void Neurone::calculeMaValeurEnFonctionDesMesConnections()
{
    // Je dois donc ajouter tout les produits poids*valeurs des mes neurones
    // connectés
    m_valeur = 0;
    for (const Neurone* n: m_neuronesConnectés)
        m_valeur += n->getPoids() * n->getValeur();

    // ce produit passer par la fonction max(0,x) sera ma valeur
    m_valeur = max(m_min,m_valeur);
}
