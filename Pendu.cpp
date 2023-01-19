#include "Pendu.h"
#include "IHMPendu.h"
#include <fstream>
#include <limits>

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
void Pendu::menu()
{
    bool fermetureProgramme = false;
    while(!fermetureProgramme)
    {
        monIHM->afficherInfoMenu();
        switch(monIHM->entrerValeurChoixMenu())
        {
            case 0:
                monIHM->afficherRegles(nombreEssaisMax);
                break;
            case 1:
                jouer();
                break;
            case 2:
                fermetureProgramme = true;
                monIHM->afficherAuRevoir();
                break;
            default:
                break;
        }
    }
}

void Pendu::jouer()
{
    monIHM->saisirNomUtilisateur();

    choisirMot();
    masquerMot();

    do
    {
        monIHM->afficherMot(motMasque);
        char lettre = '\0';
        do
        {
            lettre = monIHM->entrerUneLettre(lettre);
        } while(!estUneLettreValide(lettre));
        lettresUtilisees += lettre;
        remplacerLettre(lettre);
        monIHM->afficherPendu(echecs);
        monIHM->afficherInfos(nombreEssaisMax, echecs, lettresUtilisees);
    } while(!estFinie());

    victoire = aGagne(motADeviner, motMasque);
    monIHM->afficherResume(echecs, motADeviner, victoire, nombreEssaisMax);

    initialisationPendu();
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

bool Pendu::estUneLettreValide(char lettre)
{
    lettre = tolower(lettre);
    if(isalpha(lettre))
    {
        if(lettresUtilisees.find(lettre) != string::npos)
        {
            monIHM->afficherErreurLettreDejaUtilisee();
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        monIHM->afficherErreurLettre();
        return false;
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

void Pendu::initialisationPendu()
{
    echecs           = 0;
    motADeviner      = "";
    motMasque        = "";
    lettresUtilisees = "";
    victoire         = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // on vide tout
}