#include <poisson.hpp>

Poisson::Poisson() :
    m_maxTempsDeVie(0),
    m_epochNaissance(getEpochNow()),
    m_iTempsDeVie(0),
    m_valeursAAjouterAVarAléa(0.1f)
    /* m_minRnd(-3.14f), */
    /* m_maxRnd(3.14f) */
{
    m_forme = Cercle;
    initialiseLesVariablesAléatoires();

    for (long& tpsDeVie: m_tempsDeVie)
        tpsDeVie = 0;
}

// sub
void Poisson::calculeNouvelleAngle(const Etre::nbType directionRequin)
{
    m_angleDeDirection = directionRequin + m_variablesAléatoires[0];
}

/////////// OVERRIDE
void Poisson::renaît()
{
    // reset ma pos
    Etre::renaît();

    auto nouvelleEpoch = getEpochNow();
    auto tempsDeVie = nouvelleEpoch - m_epochNaissance;
    m_epochNaissance = nouvelleEpoch;

    m_tempsDeVie[m_iTempsDeVie] = tempsDeVie;
    m_iTempsDeVie++;

    // si les temps de vie sont plus long maintenant que la dernière fois,
    // c'est que je vais dans le bon sens, sinon je dois aller dans l'autre sens
    
    //  pour ce faire je dois récupérer la plus jeune valeurs significative, et
    //  la plus vieille
    size_t itempsDeVieLePlusRécent = Poisson::NB_TPS_DE_VIE;
    size_t itempsDeVieLePlusVieux = Poisson::NB_TPS_DE_VIE;
    size_t nombreDeValeurSignificative = 0;
    size_t i = 0;

    for (const long& ms: m_tempsDeVie)
    {
        if (ms > 0)
        {
            show("ms",ms);
            nombreDeValeurSignificative++;

            if (itempsDeVieLePlusRécent == Poisson::NB_TPS_DE_VIE) 
                itempsDeVieLePlusRécent = i;

            itempsDeVieLePlusVieux = i;
        }
        i++;
    }

    if (itempsDeVieLePlusRécent == itempsDeVieLePlusVieux)
        // alors je n'ai pas assez d'info pour savoir quelque chose, alors je ne
        // fais rien
        note("pas assez d'infos de temps de vie pour savoir quoi changer, je ne change rien");
    else
    {

        // si le poisson s'est mieux débrouillé maintenant que la dernière fois,
        // alors je continue d'avancer dans le même sens
        if (m_tempsDeVie.at(itempsDeVieLePlusRécent) > m_tempsDeVie.at(itempsDeVieLePlusVieux))
        {
            note("Je vie PLUS longtemps");
        }else
        {
            note("Je vie MOINS lontemps");
            /* m_valeursAAjouterAVarAléa *= -1; */
        }
        m_variablesAléatoires[0] += m_valeursAAjouterAVarAléa;
        show("varAléa",m_variablesAléatoires[0]);
    }

    /* m_oldTempsDeVie = tempsDeVie; */
}

// debug
void Poisson::debug() const
{
    Etre::debug();
    note("Je suis un poisson");
    show("Je suis vivant depuis",getEpochNow() - m_epochNaissance);
}

//////////////////////////////////////////////////////// PRIVATE
void Poisson::initialiseLesVariablesAléatoires()
{
    for (auto& varAlea : m_variablesAléatoires)
        varAlea = static_cast<Etre::nbType>( Rnd::_double()*3.14*2 - 3.14 );
}
