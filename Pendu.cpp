#include "Pendu.h"
#include "IHMPendu.h"
#include <fstream>

#ifdef DEBUG_PENDU
#include <iostream>
#endif

using namespace std;

Pendu::Pendu() :
    monIHM(new IHMPendu), mots{ "hello", "world", "couscous", "scooter" },
    nombreEssaisMax(NB_ESSAIS_MAX_DEFAUT), echecs(0), motADeviner(""),
    motMasque(""), victoire(false)
{
    srand(time(NULL));
}

Pendu::~Pendu()
{
    delete monIHM;
}

void Pendu::choisirMot()
{
    motADeviner = mots[rand() % mots.size()];
}

void Pendu::masquerMot()
{
    motMasque        = motADeviner;
    size_t tailleMot = motADeviner.size();
    for(size_t i = 1; i < tailleMot - 1; i++)
    {
        motMasque[i] = '_';
    }
}

void Pendu::verifierLettre(char lettre)
{
    lettre = monIHM->entrerUneLettre(lettre);
    lettre = tolower(lettre);
    if(isalpha(lettre))
    {
        if(lettresUtilisees.find(lettre) != string::npos)
        {
            monIHM->afficherErreurLettreDejaUtilisee();
        }
        else
        {
            lettresUtilisees += lettre;
            remplacerLettre(lettre);
        }
    }
    else
    {
        monIHM->afficherErreurLettre();
    }
}

void Pendu::remplacerLettre(char lettre)
{
    if(motADeviner.find(lettre) != string::npos)
    {
        for(size_t i = 0; i < motADeviner.size(); i++)
        {
            if(motADeviner[i] == lettre)
                motMasque[i] = lettre;
        }
    }
    else
    {
        echecs++;
    }
}

bool Pendu::estFinie() const
{
    return (echecs >= nombreEssaisMax || motADeviner == motMasque);
}

bool Pendu::aGagne(string motADeviner, string motMasque) const
{
    return (motADeviner == motMasque);
}

void Pendu::jouer()
{
    monIHM->afficherRegles(nombreEssaisMax);
    monIHM->saisirNomUtilisateur();

    choisirMot();
    masquerMot();

    char lettre = '\0';
    do
    {
        monIHM->afficherMot(motMasque);
        verifierLettre(lettre);
        monIHM->afficherPendu(echecs);
        monIHM->afficherInfos(nombreEssaisMax, echecs, lettresUtilisees);
    } while(!estFinie());

    victoire = aGagne(motADeviner, motMasque);
    monIHM->afficherResume(echecs, motADeviner, victoire, nombreEssaisMax);
}
