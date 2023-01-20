#include "Pendu.h"
#include "IHMPendu.h"
#include <iostream>
#include <fstream>
#include <limits>

#define DEBUG_THEME

using namespace std;

Pendu::Pendu() :
    monIHM(new IHMPendu), mots{ "" }, nombreEssaisMax(NB_ESSAIS_MAX_DEFAUT),
    echecs(0), theme(0), motADeviner(""), motMasque(""), victoire(false)
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
        int choix = monIHM->entrerValeurChoix();
        switch(choix)
        {
            case 1:
                monIHM->afficherRegles(nombreEssaisMax);
                break;
            case 2:
                jouer();
                break;
            case 3:
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
    choisirMot(theme);
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

    reinitialiserPendu();
}

string Pendu::selectionnerFichier(unsigned int theme)
{
    switch(monIHM->choisirTheme())
    {
        case 1:
            return ("listeMots/animaux");
            break;
        case 2:
            return ("listeMots/capitales");
            break;
        case 3:
            return ("listeMots/objets");
            break;
        case 4:
            return ("listeMots/pays");
            break;
        default:
            return ("listeMots/pays");
            break;
    }
}

void Pendu::choisirMot(unsigned int theme)
{
    ifstream listeMots(selectionnerFichier(theme));
#ifdef DEBUG_THEME
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__
              << "] ouvert = " << listeMots.is_open() << std::endl;
#endif
    // TODO : vérifier que le fichier est ouvert

    string mot;
    while(getline(listeMots, mot))
    {
        mots.push_back(mot);
    }
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

void Pendu::reinitialiserPendu()
{
    echecs           = 0;
    motADeviner      = "";
    motMasque        = "";
    lettresUtilisees = "";
    victoire         = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // on vide tout
}
