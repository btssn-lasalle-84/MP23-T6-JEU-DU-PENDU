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
    motMasque("")
{
#ifdef DEBUG_PENDU
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] " << this
              << std::endl;
#endif
    srand(time(NULL));
}

Pendu::~Pendu()
{
    delete monIHM;
#ifdef DEBUG_PENDU
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] " << this
              << std::endl;
#endif
}

void Pendu::choisirMot()
{
    int numeroMot = rand() % mots.size();
    motADeviner   = mots[numeroMot];

#ifdef DEBUG_PENDU
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << "numeroMot = " << numeroMot << std::endl;
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << "motADeviner = " << motADeviner << std::endl;
#endif
}

void Pendu::masquerMot()
{
    motMasque        = motADeviner;
    size_t tailleMot = motADeviner.size();
    for(size_t i = 1; i < tailleMot - 1; i++)
    {
        motMasque[i] = '_';
    }
#ifdef DEBUG_PENDU
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << "motMasque = " << motMasque << std::endl;
#endif
}

void Pendu::remplacerLettres(char lettre)
{
    lettresUtilisees += lettre;

    for(size_t i = 0; i < motADeviner.size(); i++)
    {
    }
}
void Pendu::verifierLettres()
{
    char lettre = monIHM->entrerUneLettre();
    lettre      = tolower(lettre);
    if(isalpha(lettre))
    {
        remplacerLettres(lettre);
    }
    else
    {
        monIHM->afficherErreurLettre();
    }
}

void Pendu::jouer()
{
    monIHM->afficherRegles();
    monIHM->saisirNomUtilisateur();

    // une partie
    choisirMot();
    masquerMot();
    char lettre = '\0';
    do
    {
        lettre = monIHM->entrerUneLettre();
        verifierLettres();
        // remplacerLettres(lettre);
        monIHM->afficherMot();
        monIHM->afficherInfos();
        monIHM->afficherPendu(echecs);
    } while(!estFinie());

    monIHM->afficherResume();
}

bool Pendu::estFinie() const
{
    return (echecs >= nombreEssaisMax);
}

bool Pendu::aGagne() const
{
    return (echecs < nombreEssaisMax);
}