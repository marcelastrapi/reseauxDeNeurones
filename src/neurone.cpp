#include <neurone.hpp>

Neurone::Neurone():
    m_poids(0),
    m_valeur(0),
    m_min(0)
{
    poidsAléa();
}

// setters
void Neurone::poidsAléa(const nbType min, const nbType max)
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
    note("__________ Je suis un Neurone");
    show("nombre de connexion",this->nbConnexions());
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
    {
        m_valeur += this->poids() * n->valeur();
        show("m_valeur",m_valeur);
    }

    // ce produit passer par la fonction max(0,x) sera ma valeur
    m_valeur = max(m_min,m_valeur);

    return m_valeur;
}
