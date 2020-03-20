#include <neurone.hpp>

Neurone::Neurone():
    m_poids(0),
    m_valeur(0),
    m_seuil(0)
{
    poidsAléa(0,1);
}

Neurone::Neurone(const Neurone& neuroneÀCopier)
{
    m_poids = neuroneÀCopier.poids();
    m_seuil = neuroneÀCopier.seuil();
}

// setters
void Neurone::poidsAléa(const nbType min, const nbType max)
{
    m_poids = Rnd::rnd<nbType>(min,max);
}
void Neurone::poidsAléa(const nbType fourchetteAutourDuPoids)
{
    m_poids = Rnd::rnd<nbType>(m_poids - fourchetteAutourDuPoids, m_poids + fourchetteAutourDuPoids);
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
        // TODO j'ai pris le poids du neurone d'arriver, parce que j'ai qu'une
        // entrée mais je ne suis pas sûr que ça fonctionne du coup...
        m_valeur += this->poids() * n->valeur();
        /* show("m_valeur",m_valeur); */
    }

    // ce produit passer par la fonction max(0,x) sera ma valeur
    m_valeur = max(m_seuil,m_valeur);

    return m_valeur;
}
