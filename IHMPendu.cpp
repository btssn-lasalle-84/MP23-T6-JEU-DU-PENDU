#include "IHMPendu.h"
#include <iostream>

using namespace std;

IHMPendu::IHMPendu() : lettresUtilisees(""), lettresDevinees("")
{
}

IHMPendu::~IHMPendu()
{
}

void IHMPendu::afficherRegles(const unsigned int nombreEssaisMax) const
{
    cout << "Voici les règles :" << endl << endl;
    cout
      << "1. Un mot sera choisi au hasard pour que vous essayiez de le deviner."
      << endl;
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
    cout << "Bonne chance !" << endl << endl;
}

void IHMPendu::afficherPendu(unsigned int echecs) const
{
    string dessin_pendu[NB_LIGNE_DESSIN_PENDU] = {
        "  ____\n |    |\n |\n |\n |\n |\n |",
        "  ____\n |    |\n |    O\n |\n |\n |\n |",
        "  ____\n |    |\n |    O\n |   /\n |\n |\n |",
        "  ____\n |    |\n |    O\n |   /|\n |\n |\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |\n |\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |   /\n |\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |   / \\\n |\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |   / \\\n |   -\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |   / \\\n |   - -\n |",
        "  ____\n |    |\n |    O\n |   /|\\\n |   / \\\n |   ---\n |"
    };
    cout << dessin_pendu[echecs] << endl;
}

void IHMPendu::afficherMot(string motMasque) const
{
    cout << "Mot à deviner : ";
    for(size_t i = 0; i < motMasque.size(); i++)
    {
        cout << motMasque[i];
        cout << " ";
    }
    cout << endl;
}

void IHMPendu::afficherInfos(const unsigned int nombreEssaisMax,
                             unsigned int       echecs,
                             string             lettresUtilisees) const
{
    if((nombreEssaisMax - echecs) > 0)
    {
        cout << "Nombre d'essais restants : " << nombreEssaisMax - echecs
             << endl;
        cout << "Lettres déjà utilisées : " << lettresUtilisees << endl;
    }
}

void IHMPendu::afficherResume(unsigned int       echecs,
                              string             motADeviner,
                              bool               victoire,
                              const unsigned int nombreEssaisMax) const
{
    if(victoire)
    {
        cout << "Bravo " << nom << " ! Vous avez trouvé le mot en " << echecs
             << " tentative" << ((echecs > 1) ? ("s") : ("")) << endl
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
    cout << "Saisisez votre pseudo : ";
    cin >> nom;
    return nom;
}

char IHMPendu::entrerUneLettre(char lettre)
{
    cout << "lettre : ";
    cin >> lettre;
    return lettre;
}

void IHMPendu::afficherErreurLettre() const
{
    cout << "La lettre saisie n'est pas valide. Veuillez saisir une lettre de "
            "l'alphabet (sans accent et insensible à la casse)."
         << endl;
}

void IHMPendu::afficherErreurLettreDejaUtilisee() const
{
    cout << "Vous avez déja entré cette lettre" << endl;
}

void IHMPendu::afficherInfoMenu() const
{
    cout << "Bienvenue à la version " << VERSION << " du jeu du pendu !" << endl
         << endl;

    cout << "0. Afficher les règles" << endl;
    cout << "1. Jouer au jeu" << endl;
    cout << "2. Quitter" << endl;
}
unsigned int IHMPendu::entrerValeurChoixMenu()
{
    unsigned int choix;
    cout << endl << "Entrez votre choix : ";
    cin >> choix;
    return choix;
}

void IHMPendu::afficherAuRevoir() const
{
    cout << endl << "Merci d'avoir joué " << endl;
}
