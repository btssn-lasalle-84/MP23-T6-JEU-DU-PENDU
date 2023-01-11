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

void Pendu::remplacerLettres(char lettre)
{
    lettresUtilisees += lettre;

    if(motADeviner.find(lettre) != string::npos)
    {
        for(size_t i = 0; i < motADeviner.size(); i++)
        {
            if(motADeviner[i] == lettre)
            {
                motMasque[i] = lettre;
            }
        }
    }
    else
    {
        echecs++;
    }
}

void Pendu::jouer()
{
    monIHM->afficherRegles();
    monIHM->saisirNomUtilisateur();

    // une partie
    choisirMot();
    char lettre = '\0';
    do
    {
        lettre = monIHM->entrerUneLettre();
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