#pragma once

#include <vector>

#include <utils.hpp>
/* #include <displayer.hpp> */
/* using namespace displayer; */

#include <rnd.hpp>

typedef float nbType;

class Neurone
{
    public:
        struct Connexion
        {
            nbType poids;
            Connexion(nbType _poids = 0):poids(_poids) {}
            inline bool operator== (const Connexion& toTest) const
            { return this->poids == toTest.poids; }
            inline bool operator!= (const Connexion& toTest) const
            { return this->poids != toTest.poids; }

            void poidsAléa(const nbType min, const nbType max)
            { poids = Rnd::_float(min,max); }
            void poidsAléa(const nbType fourchetteAutourDuPoids)
            {
                poids += Rnd::_float( -fourchetteAutourDuPoids, fourchetteAutourDuPoids);
                // TODO rendre accessible les limites
            }
        };

        using Neurones = std::vector<Neurone>;
        using Connexions = std::vector<Connexion>;

        Neurone(const nbType val = 0, const bool estUnBiais = false);
        Neurone(const Neurone& neuroneÀCopier);

        // operator
        bool operator==(const Neurone& otherNeurone) const;
        bool operator!=(const Neurone& otherNeurone) const;

        // setters
        void poidsAléa(const nbType, const nbType max);
        void poidsAléa(const nbType fourchetteAutourDuPoids);
        inline void poids (const nbType _poids ) { m_poids  = _poids ; }
        inline void seuil (const nbType _seuil ) { m_seuil  = _seuil ; }
        inline void valeur(const nbType _valeur) { m_valeur = _valeur; }
        void lignePrécédente(Neurones&);

        // getters
        nbType valeur() const { return m_valeur; }
        nbType seuil() const { return m_seuil; }
        size_t nbConnexions() const { return m_connexions.size(); }
        Connexions connexions() const { return m_connexions; }

        // sub
        void print() const;

        // functions
        nbType calculeMaValeurEnFonctionDesMesConnexions();

        bool estUnBiais;
    protected:
        nbType m_poids;
        nbType m_seuil;
        nbType m_valeur;
        // vector de pointeur vers les neurones qui sont connecté à moi
        Neurones* m_lignePrécédente;
        Connexions m_connexions;

    public:
        static void CONNECTE_NEURONES_À_NEURONES(Neurones& ligne1, Neurones& ligne2)
        {
            for (Neurone& n: ligne2)
                n.lignePrécédente(ligne1);
        }

};
