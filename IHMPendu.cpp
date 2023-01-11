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

void IHMPendu::afficherInfos()
{
}

void IHMPendu::afficherMot()
{
}

void IHMPendu::afficherResume()
{
}
string IHMPendu::saisirNomUtilisateur()
{
    string nom;
    cout << "Saisisez votre pseudo : ";
    cin >> nom;
    return nom;
}

char IHMPendu::entrerUneLettre()
{
    // vérifier si c'est une lettre "valide" (c)
    char lettre = '\0';
    cout << "lettre : ";
    cin >> lettre;
    return lettre;
}
