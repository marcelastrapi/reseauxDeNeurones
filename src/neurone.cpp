#include <neurone.hpp>

/* Neurone::Neurone(): */
/*     m_valeur(0), estUnBiais(false) */
/* { } */
Neurone::Neurone(const nbType val, const bool estUnBiais):
    estUnBiais(estUnBiais), m_valeur(val)
{ }
Neurone::Neurone(const Neurone& neuroneÀCopier)
{
    m_valeur = neuroneÀCopier.m_valeur;
    estUnBiais = neuroneÀCopier.estUnBiais;
    m_connexions = neuroneÀCopier.connexions();
}

// operators
bool Neurone::operator==(const Neurone& otherNeurone) const
{
    if (otherNeurone.nbConnexions() != nbConnexions())
        return false;

    for (size_t i = 0; i < otherNeurone.nbConnexions(); i++) {
        if (m_connexions.at(i) != otherNeurone.m_connexions.at(i))
            return false;
    }
    return true;
}
bool Neurone::operator!=(const Neurone& otherNeurone) const
{
    if (otherNeurone.nbConnexions() != nbConnexions())
        return true;

    for (size_t i = 0; i < otherNeurone.nbConnexions(); i++) {
        if (m_connexions.at(i) != otherNeurone.m_connexions.at(i))
            return true;
    }
    return false;
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
    if (this->estUnBiais){
        note("__________ Je suis un Biais");
    }else{
        note("__________ Je suis un Neurone");
        show("nombre de connexion",this->nbConnexions());
        for (auto& c: m_connexions)
            show("poids",c.poids);
    }
    show("valeurs",m_valeur);
}

// functions
nbType Neurone::calculeMaValeurEnFonctionDesMesConnexions()
{
    if (this->estUnBiais) {
        return m_valeur;
    }

    // Je dois donc ajouter tout les produits poids*valeurs des mes neurones
    // connectés
    m_valeur = 0;
    size_t i(0);
    for (const Neurone& n: *m_lignePrécédente)
    {
        m_valeur += m_connexions.at(i++).poids * n.valeur();
    }

    // fast sigmoid
    if ((m_valeur < -1) || (m_valeur > 1))
    {
        m_valeur = m_valeur / (1 + abs(m_valeur));
    }

    /* m_valeur /= this->nbConnexions(); */

    return m_valeur;
}
