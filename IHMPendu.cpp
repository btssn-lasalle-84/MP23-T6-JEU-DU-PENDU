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

void IHMPendu::afficherMot(string motMasque)
{
    cout << "Mot à deviner : " << motMasque << endl;
}

void IHMPendu::afficherInfos(const unsigned int nombreEssaisMax,
                             unsigned int       echecs,
                             string             lettresUtilisees)
{
    cout << "Nombre d'essais restant : " << nombreEssaisMax - echecs << endl;
    cout << "Lettres déjà utilisées : " << lettresUtilisees << endl;
}

void IHMPendu::afficherResume(unsigned int       echecs,
                              string             motADeviner,
                              bool               victoire,
                              const unsigned int nombreEssaisMax)
{
    if(victoire)
    {
        cout << "Bravo ! Vous avez trouvé le mot avec "
             << nombreEssaisMax - echecs << " tentatives restantes" << endl;
    }
    else
    {
        cout << "Aïe ! Vous avez atteint la limite de tentatives, le mot était "
             << motADeviner << endl;
    }
}

string IHMPendu::saisirNomUtilisateur()
{
    string nom;
    cout << "Saisisez votre pseudo : ";
    cin >> nom;
    return nom;
}

char IHMPendu::entrerUneLettre(char lettre)
{
    lettre = '\0';
    cout << "lettre : ";
    cin >> lettre;
    return lettre;
}

void IHMPendu::afficherErreurLettre()
{
    cout << "La lettre saisie n'est pas valide. Veuillez saisir une lettre de "
            "l'alphabet (sans accent et insensible à la casse)."
         << endl;
}

void IHMPendu::afficherErreurLettreDejaUtilisee()
{
    cout << "Vous avez déja entrée cette lettre" << endl;
}
