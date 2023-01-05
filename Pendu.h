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
    unsigned int             nombreEssaisMax;
    unsigned int             echecs;
    std::string              motADeviner;
    std::string              motActuel;
    std::string              lettresUtilisees;

  public:
    Pendu();
    ~Pendu();

    void choisirMot();
    void jouer();
    void chercherLettre(char lettre);
    bool aGagne();
};

#endif