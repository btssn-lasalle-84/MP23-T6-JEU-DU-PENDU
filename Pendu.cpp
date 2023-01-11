#include "Pendu.h"
#include "IHMPendu.h"
#include <fstream>

using namespace std;

Pendu::Pendu() :
    monIHM(new IHMPendu), mots{ "hello", "world", "couscous", "scooter" },
    nombreEssaisMax(NB_ESSAIS_MAX_DEFAUT), motADeviner(""), motActuel("")
{
}

Pendu::~Pendu()
{
    delete monIHM;
}

void Pendu::choisirMot()
{
    unsigned int nombreMots;

    ifstream file("list/dictionaire.txt");
    for(nombreMots = 0; file >> motADeviner; nombreMots++)
    {
    }

    srand(time(NULL));
    int randomIndex = rand() % nombreMots;
    file.clear();

    file.seekg(0, ios::beg);
    for(unsigned int j = 0; j < randomIndex; j++)
    {
        file >> motADeviner;
    }
}

void Pendu::chercherLettre(char lettre)
{
    lettresUtilisees += lettre;

    if(motADeviner.find(lettre) != string::npos)
    {
        for(int i = 0; i < motADeviner.size(); i++)
        {
            if(motADeviner[i] == lettre)
            {
                motActuel[i] = lettre;
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
    choisirMot();
}

bool Pendu::aGagne()
{
    if(echecs == nombreEssaisMax)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}