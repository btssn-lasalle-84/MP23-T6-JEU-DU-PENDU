#include "Pendu.h"
#include "IHMPendu.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

// #define DEBUG_THEME

using namespace std;

Pendu::Pendu() :
    monIHM(new IHMPendu), mots{ "" }, nombreEssaisMax(NB_ESSAIS_MAX_DEFAUT),
    nombreCaracteresMaxFacile(DIFFICULTE_FACILE),
    nombreCaracteresMaxMoyen(DIFFICULTE_MOYEN), echecs(0), theme(0),
    difficulte(1), temps(0), score(0), motADeviner(""), motMasque(""),
    victoire(false)
{
    srand(time(NULL));
}

Pendu::~Pendu()
{
    delete monIHM;
}
void Pendu::menu()
{
    bool fermetureProgramme = false;
    while(!fermetureProgramme)
    {
        monIHM->afficherInfoMenu();
        int choix = monIHM->entrerValeurChoix();
        system("clear");
        switch(choix)
        {
            case 1:
                monIHM->afficherRegles(nombreEssaisMax);
                break;
            case 2:
                jouer();
                break;
            case 3:
                monIHM->afficherHistorique();
                break;
            case 4:
                fermetureProgramme = true;
                monIHM->afficherAuRevoir();
                break;

            default:
                break;
        }
    }
}

void Pendu::jouer()
{
    monIHM->saisirNomUtilisateur();
    difficulte = monIHM->choisirDifficulte();
    system("clear");
    definirMot(theme, difficulte);
    masquerMot();

    int debutChrono = time(NULL);
    do
    {
        monIHM->afficherMot(motMasque);
        char lettre = '\0';
        do
        {
            lettre = toupper(monIHM->entrerUneLettre(lettre));
        } while(!estUneLettreValide(lettre));

        lettresUtilisees += lettre;
        system("clear");

        remplacerLettre(lettre);
        monIHM->afficherPendu(echecs);
        monIHM->afficherInfos(nombreEssaisMax, echecs, lettresUtilisees);
    } while(!estFinie());

    temps = time(NULL) - debutChrono;

    victoire = aGagne(motADeviner, motMasque);

    monIHM->afficherResume(echecs,
                           motADeviner,
                           victoire,
                           nombreEssaisMax,
                           temps);

    if(echecs != 0)
        score = (1000 / ((echecs * temps) / motADeviner.size()));
    else
        score = (1000 / (temps / motADeviner.size()));

    sauvegarderHistorique();
    reinitialiserPendu();
}

string Pendu::selectionnerFichier(unsigned int theme)
{
    switch(monIHM->choisirTheme())
    {
        case 1:
            return ("listeMots/dictionnaire_francais.txt");
            break;
        case 2:
            return ("listeMots/capitales");
            break;
        case 3:
            return ("listeMots/objets");
            break;
        case 4:
            return ("listeMots/pays");
            break;
        case 5:
            return ("listeMots/animaux");
            break;
        default:
            return ("listeMots/dictionnaire_francais.txt");
            break;
    }
}

void Pendu::definirMot(unsigned int theme, unsigned int difficulte)
{
    ifstream listeMots(selectionnerFichier(theme));
#ifdef DEBUG_THEME
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__
              << "] ouvert = " << listeMots.is_open() << std::endl;
#endif
    if(listeMots.is_open())
    {
        string mot;
        do
        {
            while(getline(listeMots, mot))
            {
                mots.push_back(mot);
            }
            motADeviner = mots[rand() % mots.size()];
#ifdef DEBUG_PENDU
            std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__
                      << "] Mot à deviner = " << motADeviner << std::endl;
#endif
        } while(!estDeLaBonneTaille(difficulte,
                                    motADeviner,
                                    nombreCaracteresMaxFacile,
                                    nombreCaracteresMaxMoyen));
    }
    else
    {
        monIHM->afficherErreurOuvertureFichier();
    }
}

bool Pendu::estDeLaBonneTaille(unsigned int       difficulte,
                               string             motADeviner,
                               const unsigned int nombreCaracteresMaxFacile,
                               const unsigned int nombreCaracteresMaxMoyen)
{
    switch(difficulte)
    {
        case 1:
            return true;
            break;
        case 2:
            return (motADeviner.size() <= nombreCaracteresMaxFacile);
            break;
        case 3:
            return ((motADeviner.size() > nombreCaracteresMaxFacile) &&
                    (motADeviner.size() <= nombreCaracteresMaxMoyen));
            break;
        case 4:
            return (motADeviner.size() > nombreCaracteresMaxMoyen);
        default:
            return true;
            break;
    }
}

void Pendu::masquerMot()
{
    motMasque        = motADeviner;
    size_t tailleMot = motADeviner.size();
    for(size_t i = 1; i < tailleMot - 1; i++)
    {
        motMasque[i] = '_';
    }
}

bool Pendu::estUneLettreValide(char lettre)
{
    if(isalpha(lettre))
    {
        if(lettresUtilisees.find(lettre) != string::npos)
        {
            monIHM->afficherErreurLettreDejaUtilisee();
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        monIHM->afficherErreurLettre();
        return false;
    }
}

void Pendu::remplacerLettre(char lettre)
{
    if(motADeviner.find(lettre) != string::npos)
    {
        for(size_t i = 0; i < motADeviner.size(); i++)
        {
            if(motADeviner[i] == lettre)
                motMasque[i] = lettre;
        }
    }

    else
    {
        echecs++;
    }
}

bool Pendu::estFinie() const
{
    return (echecs >= nombreEssaisMax || motADeviner == motMasque);
}

bool Pendu::aGagne(string motADeviner, string motMasque) const
{
    return (motADeviner == motMasque);
}

void Pendu::reinitialiserPendu()
{
    echecs           = 0;
    motADeviner      = "";
    motMasque        = "";
    lettresUtilisees = "";
    victoire         = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // on vide tout
}

void Pendu::sauvegarderHistorique()
{
    ofstream fichierHistorique("historique.txt", ios::app);
    if(fichierHistorique.is_open())
    {
        string victoire = (this->victoire) ? "Oui" : "Non";

        fichierHistorique << "| " << left << setw(6) << setfill(' ') << score
                          << " | " << left << setw(15) << setfill(' ')
                          << monIHM->getNomUtilisateur() << " | " << left
                          << setw(15) << setfill(' ') << motADeviner << " | "
                          << left << setw(10) << setfill(' ') << difficulte
                          << " | " << left << setw(6) << setfill(' ') << echecs
                          << " | " << left << setw(5) << setfill(' ') << temps
                          << " | " << left << setw(8) << setfill(' ')
                          << victoire << " |" << endl;
        fichierHistorique.close();
        definitionNbLigneHistoriquePendu();
    }
    else
    {
        monIHM->afficherErreurOuvertureFichierHistorique();
    }
}

void Pendu::definitionNbLigneHistoriquePendu()
{
    ifstream       ifs("historique.txt", ios::in);
    vector<string> lines;
    string         line;
    while(getline(ifs, line))
    {
        lines.push_back(line);
    }
    ifs.close();

    if(lines.size() > 10) // si il y a plus de 10 lignes (10 parties)
    {
        lines.erase(lines.begin()); // on supprime la plus ancienne partie
    }

    ofstream ofs("historique.txt", ios::out | ios::trunc);
    for(const auto& l: lines)
    {
        ofs << l << endl;
    }
    ofs.close();
}