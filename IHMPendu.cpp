#include "IHMPendu.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <iomanip>

using namespace std;

IHMPendu::IHMPendu() : lettresUtilisees(""), lettresDevinees("")
{
}

IHMPendu::~IHMPendu()
{
}

void IHMPendu::afficherRegles(const unsigned int nombreEssaisMax) const
{
    cout << "Voici les règles :" << endl << endl
      << "1. Un mot sera choisi au hasard pour que vous essayiez de le deviner."
      << endl << "2. Vous aurez un maximum de " << nombreEssaisMax
         << " tentatives pour deviner le mot correctement." << endl << "3. Vous pouvez deviner une lettre à la fois. Si la lettre est "
            "dans le mot, elle sera révélée à la bonne position."
         << endl << "4. Si la lettre n'est pas dans le mot, vous perdrez une tentative."
         << endl << "5. Si vous révélez le mot entier avant d'épuiser vos tentatives, "
            "vous gagnez le jeu."
         << endl << "6. Si vous épuisez vos tentatives avant de révéler le mot entier, "
            "vous perdez le jeu."
         << endl << "7. Le score est calculé en fonction de la difficulté, du nombre de tentatives et du temps prit pour deviner le mot." << endl
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
                              const unsigned int nombreEssaisMax,
                              unsigned int       temps) const
{
    if(victoire)
    {
        if(echecs == 0)
        {
            cout << "Bravo " << nom
                 << " ! Vous avez trouvé le mot du premier coup en "
                 << ((temps >= 60) ? ((temps % 60) + temps) : (temps))
                 << " secondes !" << endl
                 << endl;
        }
        else
        {
            cout << "Bravo " << nom << " ! Vous avez trouvé le mot en "
                 << echecs << " tentative"
                 << ((echecs != 1) ? ("s, et en ") : (", et en ")) << temps
                 << " secondes." << endl
                 << endl;
        }
    }
    else
    {
        cout << "Aïe ! Vous avez atteint la limite de tentatives, le mot était "
             << motADeviner << endl
             << endl;
    }
}

string IHMPendu::saisirNomUtilisateur()
{
    cout << "Saisisez votre pseudo : ";
    cin >> nom;
    system("clear");
    cout << "Bienvenue " << nom << endl;
    return nom;
}
string IHMPendu::getNomUtilisateur()
{
    return nom;
}

unsigned int IHMPendu::choisirDifficulte()
{
    cout << endl
         << "Choississez un niveau de difficulté:" << endl
         << "1: Nombre de caractères aléatoire" << endl
         << "2: Facile (entre 3 et 4 caractères)" << endl
         << "3: Moyen (entre 5 et 6 caractères)" << endl
         << "4: Difficile (plus de 7 caractères)";
    return (entrerValeurChoix());
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

unsigned int IHMPendu::choisirTheme()
{
    cout << endl
         << "Choississez un thème:" << endl
         << "1: General " << endl
         << "2: Capitales" << endl
         << "3: Objets" << endl
         << "4: Pays" << endl
         << "5: Animaux";
    return (entrerValeurChoix());
}

void IHMPendu::afficherInfoMenu() const
{
    cout << "Bienvenue à la version " << VERSION << " du jeu du pendu !" << endl
         << endl;

    cout << "1. Afficher les règles" << endl;
    cout << "2. Jouer au jeu" << endl;
    cout << "3. Historique" << endl;
    cout << "4. Quitter" << endl;
}

unsigned int IHMPendu::entrerValeurChoix()
{
    unsigned int choix = 0;
    while(true)
    {
        cout << endl << "Entrez votre choix : ";
        cin >> choix;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            afficherErreurChoix();
            continue;
        }
        break;
    }
    system("clear");
    return choix;
}

void IHMPendu::afficherAuRevoir() const
{
    cout << endl << "Merci d'avoir joué " << endl;
}
void IHMPendu::afficherErreurChoix() const
{
    cerr << "Erreur: veuillez saisir un entier" << endl;
}

void IHMPendu::afficherErreurOuvertureFichier() const
{
    cerr << "Impossible d'ouvrir le fichier" << endl;
}

void IHMPendu::afficherHistorique()
{
    cout << "| Score  | Nom Utilisateur |       Mot       | Difficulté | Echecs | Temps | Victoire |"
         << endl;
    cout << "|        |                 |                 |            |        |       |          |"
         << endl;
    ifstream fichierHistorique("historique.txt");
    if(fichierHistorique.is_open())
    {
        string ligne;
        while(getline(fichierHistorique, ligne))
        {
            cout << ligne << endl;
        }
    }
    else
    {
        cout << "Aucun historique de parties disponible." << endl;
    }
    cout << endl;
    fichierHistorique.close();
}

void IHMPendu::afficherErreurOuvertureFichierHistorique()
{
    cout << "Impossible d'ouvrir le fichier historique.txt" << endl;
}