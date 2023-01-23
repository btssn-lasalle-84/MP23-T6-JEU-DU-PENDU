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
        return ("listeMots/dictionnaire_francais.txt");
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
    case 5:
        return ("listeMots/animaux");
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
    if (listeMots.is_open())
    {
        string mot;
        while (getline(listeMots, mot))
        {
            mots.push_back(mot);
        }
        motADeviner = mots[rand() % mots.size()];
    }
    else
    {
        monIHM->afficherErreurFichierOuvert();
    }
}

void Pendu::masquerMot()
{
    motMasque        = motADeviner;
    size_t tailleMot = motADeviner.size();
    for (size_t i = 0; i < tailleMot; i++)
    {
        motMasque[i] = '*';
    }
}

bool Pendu::estUneLettreValide(char lettre)
{
    if (!isalpha(lettre))
    {
        monIHM->afficherErreurSaisieLettre();
        return false;
    }
    if (lettresUtilisees.find(lettre) != string::npos)
    {
        monIHM->afficherLettreDejaSaisie(lettre);
        return false;
    }
    return true;
}

void Pendu::remplacerLettre(char lettre)
{
    size_t tailleMot = motADeviner.size();
    bool   lettreTrouvee = false;
    for (size_t i = 0; i < tailleMot; i++)
    {
        if (motADeviner[i] == lettre)
        {
            motMasque[i] = lettre;
            lettreTrouvee = true;
        }
    }
    if (!lettreTrouvee)
    {
        echecs++;
    }
}

bool Pendu::estFinie()
{
    return (echecs >= nombreEssaisMax) || (motMasque == motADeviner);
}

bool Pendu::aGagne(string motADeviner, string motMasque)
{
    return motADeviner == motMasque;
}

void Pendu::reinitialiserPendu()
{
    echecs        = 0;
    motADeviner   = "";
    motMasque     = "";
    lettresUtilisees = "";
    victoire      = false;
}
