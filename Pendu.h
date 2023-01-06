#ifndef PENDU_H
#define PENDU_H

#include <vector>
#include <string>

#define NB_ESSAIS_MAX_DEFAUT 8

class IHMPendu;

class Pendu
{
  private:
    IHMPendu*                monIHM;
    std::vector<std::string> mots;
    std::string              motActuel;
    unsigned int             echecs;
    unsigned int             nombreEssaisMax;
    std::string              motADeviner;
    std::string              lettresUtilisees;

  public:
    Pendu();
    ~Pendu();

    std::string  getMotADeviner();
    std::string  getMotActuel();
    unsigned int getEchecsMax();
    unsigned int getEchecs();

    void jouer();
    void choisirMot();
    void chercherLettre(char lettre);
    bool aGagne();
};
#endif
