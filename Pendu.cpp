#include "Pendu.h"
#include "IHMPendu.h"
#include <iostream>
using namespace std;

Pendu::Pendu() :
    monIHM(new IHMPendu), mots{ "hello", "world", "couscous", "scooter" },
    nombreEssaisMax(NB_ESSAIS_MAX_DEFAUT), motADeviner(""), motActuel(""),
    echecs(0)
{
    // 1. initialiser le générateur !
    // 2. c'est une méthode
    // std::string motADeviner = mots[rand() % mots.size()];
    // string motActuel(motADeviner.size(), '-'); // A _ _ _ Z
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

/*

void Pendu::chercherLettre(char lettre)
{
    lettresUtilisees += lettre;

    if(motADeviner.find(lettre) != string::npos)
    {
        cout << "Bien joué!" << endl;
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
        cout << "Faux!" << endl;
        echecs++;
    }
    //dessin(unsigned int echecs);
}
*/
void Pendu::jouer()
{
    monIHM->afficherRegles();
}