#include <neurone.hpp>

Neurone::Neurone():
    m_valeur(0),
    m_seuil(0)
{ }
Neurone::Neurone(const Neurone& neuroneÀCopier)
{
    m_connexions = neuroneÀCopier.connexions();
    m_seuil = neuroneÀCopier.seuil();
}

// setters
void Neurone::poidsAléa(const nbType min, const nbType max)
{ for (auto& c: m_connexions) c.poidsAléa(min,max); }

void Neurone::poidsAléa(const nbType fourchetteAutourDuPoids)
{ for (auto& c: m_connexions) c.poidsAléa(fourchetteAutourDuPoids); }


void Neurone::lignePrécédente(Neurones& ligne)
{
    m_connexions.resize(ligne.size());
    m_lignePrécédente = &ligne;
}
// getters

// sub
void Neurone::print() const
{
    note("__________ Je suis un Neurone");
    show("nombre de connexion",this->nbConnexions());
    show("m_seuil",m_seuil);
    for (auto& c: m_connexions)
        show("poids",c.poids);
    show("valeurs",m_valeur);
}

// functions
nbType Neurone::calculeMaValeurEnFonctionDesMesConnexions()
{
    // Je dois donc ajouter tout les produits poids*valeurs des mes neurones
    // connectés
    m_valeur = 0;
    size_t i(0);
    for (const Neurone& n: *m_lignePrécédente)
    {
        m_valeur += m_connexions.at(i++).poids * n.valeur();
    }

    // ce produit passer par la fonction max(0,x) sera ma valeur
    m_valeur = max(m_seuil,m_valeur);

    return m_valeur;
}
