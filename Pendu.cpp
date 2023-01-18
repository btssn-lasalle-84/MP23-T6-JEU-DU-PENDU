#include "Pendu.h"
#include "IHMPendu.h"
#include <fstream>

#ifdef DEBUG_PENDU
#include <iostream>
#endif

using namespace std;

Pendu::Pendu() :
    monIHM(new IHMPendu), mots{ "hello", "world", "couscous", "scooter" },
    nombreEssaisMax(NB_ESSAIS_MAX_DEFAUT), echecs(0), theme(0), motADeviner(""),
    motMasque(""), victoire(false)
{
    srand(time(NULL));
}

Pendu::~Pendu()
{
    delete monIHM;
}

string Pendu::selectionnerFichier(unsigned int theme)
{
    switch(theme)
    {
        case 1:
            return ("listeMots/animaux.txt");
            break;
        case 2:
            return ("listeMots/capitales.txt");
            break;
        case 3:
            return ("listeMots/objets.txt");
            break;
        case 4:
            return ("listeMots/pays.txt");
            break;
        default:
            return ("listeMots/pays.txt");
            break;
    }
}

void Pendu::choisirMot()
{
    unsigned int nombreMots;
    ifstream     file(selectionnerFichier(theme));
    for(nombreMots = 0; file >> motADeviner; nombreMots++)
    {
    }

    srand(time(NULL));
    int randomIndex = rand() % nombreMots;
    file.clear();

    file.seekg(0, ios::beg);
    for(size_t j = 0; j < randomIndex; j++)
    {
        file >> motADeviner;
    }
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

void Pendu::jouer()
{
    monIHM->afficherRegles(nombreEssaisMax);
    monIHM->saisirNomUtilisateur();

    unsigned int theme = monIHM->choisirTheme();
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
}
