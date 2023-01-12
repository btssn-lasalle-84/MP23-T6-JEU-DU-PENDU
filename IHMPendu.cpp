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

void IHMPendu::afficherRegles(const unsigned int nombreEssaisMax)
{
    cout << "Bienvenue au jeu du pendu ! Voici les règles :" << endl << endl;
    cout << "1. Un mot sera choisi au hasard pour que vous deviniez." << endl;
    cout << "2. Vous aurez un maximum de " << nombreEssaisMax
         << " tentatives pour deviner le mot correctement." << endl;
    cout << "3. Vous pouvez deviner une lettre à la fois. Si la lettre est "
            "dans le mot, elle sera révélée à la bonne position."
         << endl;
    cout << "4. Si la lettre n'est pas dans le mot, vous perdrez une tentative."
         << endl;
    cout << "5. Si vous révélez le mot entier avant d'épuiser vos tentatives, "
            "vous gagnez le jeu."
         << endl;
    cout << "6. Si vous épuisez vos tentatives avant de révéler le mot entier, "
            "vous perdez le jeu."
         << endl
         << endl;
    cout << "Bonne chance ! Commençons le jeu." << endl << endl;
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
