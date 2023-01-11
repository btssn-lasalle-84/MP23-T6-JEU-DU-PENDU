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

#ifdef DEBUG_PENDU
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << "motMasque = " << motMasque << std::endl;
#endif
}

void Pendu::remplacerLettre(char lettre)
{
    lettresUtilisees += lettre;
#ifdef DEBUG_PENDU
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] "
              << "lettresUtilisees = " << lettresUtilisees << std::endl;
#endif

    for(size_t i = 0; i < motADeviner.size(); i++)
    {
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
        remplacerLettre(lettre);
        monIHM->afficherMot(motMasque);
        monIHM->afficherInfos(nombreEssaisMax, echecs, lettresUtilisees);
        monIHM->afficherPendu(echecs);
    } while(!estFinie());

    monIHM->afficherResume(echecs, nombreEssaisMax, motADeviner);
}

bool Pendu::estFinie() const
{
    return (echecs >= nombreEssaisMax || motADeviner == motMasque);
}

bool Pendu::aGagne() const
{
    return (motADeviner == motMasque);
}