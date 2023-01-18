#ifndef PENDU_H
#define PENDU_H

#include <vector>
#include <string>

#define DEBUG_PENDU

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
    std::string              motMasque;
    std::string              lettresUtilisees;
    bool                     victoire;

  public:
    Pendu();
    ~Pendu();

    void choisirMot();
    void masquerMot();
    void jouer();
    bool estUneLettreValide(char lettre);
    void remplacerLettre(char lettre);
    bool estFinie() const;
    bool aGagne(std::string motADeviner, std::string motMasque) const;
};

#endif
