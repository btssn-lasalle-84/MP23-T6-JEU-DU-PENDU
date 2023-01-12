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
    if(echecs >= NB_ESSAIS_MAX_DEFAUT)
        echecs = NB_ESSAIS_MAX_DEFAUT - 1;
    string dessin_pendu[NB_ESSAIS_MAX_DEFAUT] = {
        "  ____\n |    |\n |\n |\n |\n |\n |",
        "  ____\n |    |\n |    O\n |\n |\n |\n |",
        "  ____\n |    |\n |    O\n |   /|\n |\n |\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |\n |\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |   /\n |\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |   / \\\n |\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |   / \\\n |   '\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |   / \\\n |    ---\n |"
    };
    cout << dessin_pendu[echecs] << std::endl;
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
    afficherPendu(echecs);
}

void IHMPendu::afficherResume(unsigned int echecs,
                              string       motADeviner,
                              bool         victoire)
{
    if(victoire)
    {
        cout << "Bravo ! Vous avez trouvé le mot en " << echecs << " tentatives"
             << endl;
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

char IHMPendu::entrerUneLettre()
{
    // vérifier si c'est une lettre "valide" (c)
    char lettre = '\0';
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
