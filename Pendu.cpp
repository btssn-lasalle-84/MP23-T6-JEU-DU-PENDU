#include "Pendu.h"
#include "IHMPendu.h"

#include <fstream>

using namespace std;

Pendu::Pendu() :
    monIHM(new IHMPendu), mots{ "hello", "world", "couscous", "scooter" },
    nombreEssaisMax(NB_ESSAIS_MAX_DEFAUT), motADeviner(""), motActuel(""),
    echecs(0)
{

}

Pendu::~Pendu()
{
    delete monIHM;
}

string Pendu::getMotActuel()
{
    return this->motActuel;
}

unsigned int Pendu::getEchecs()
{
    return this->echecs;
}

unsigned int Pendu::getEchecsMax()
{
    return this->nombreEssaisMax;
}

string Pendu::getMotADeviner()
{
    return this->motADeviner;
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