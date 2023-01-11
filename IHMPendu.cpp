#include "IHMPendu.h"
#include "Pendu.h"
#include <iostream>

using namespace std;

IHMPendu::IHMPendu() : lettresUtilisees(""), lettresDevinees("")
{
}

IHMPendu::~IHMPendu()
{
}

void IHMPendu::afficherRegles()
{
    cout << "Jeu du pendu" << endl;
}

void IHMPendu::afficherPendu(unsigned int echecs)
{
    if(echecs >= 1)
    {
        cout << " O";
    }
    if(echecs >= 2)
    {
        cout << "\n |";
    }
    if(echecs >= 3)
    {
        cout << "\n/|\\";
    }
    if(echecs >= 4)
    {
        cout << "\n |";
    }
    if(echecs >= 5)
    {
        cout << "\n/ \\";
    }
    cout << endl;
}

void IHMPendu::nomUtilisateur()
{
    string nom;
    cout << "Saisisez Votre pseudo";
    cin >> nom;
}

void IHMPendu::afficherInfos()
{
}

void IHMPendu::entrerUneLettre()
{
    // vérifier si c'est une lettre "valide" (c)

    pendu.remplacerLettres(char lettre);
}

void IHMPendu::afficherMot()
{
}

void IHMPendu::afficherResume()
{
    if(Pendu::aGagne())
    {
        cout << "Perdu ! ";
    }
    else
    {
        cout << "Trouvé ! ";
    }
    cout << "Le mot était " << pendu.getMotADeviner << endl;
}