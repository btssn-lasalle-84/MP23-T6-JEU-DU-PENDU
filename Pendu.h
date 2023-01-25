#ifndef PENDU_H
#define PENDU_H

#include <vector>
#include <string>

#define DEBUG_PENDU
#define DEBUG_CHOIX

#define NB_ESSAIS_MAX_DEFAUT 8

#define DIFFICULTE_FACILE 4
#define DIFFICULTE_MOYEN  6

class IHMPendu;

class Pendu
{
  private:
    IHMPendu*                monIHM;
    std::vector<std::string> mots;
    const unsigned int       nombreEssaisMax;
    const unsigned int       nombreCaracteresMaxFacile;
    const unsigned int       nombreCaracteresMaxMoyen;
    unsigned int             echecs;
    unsigned int             theme;
    unsigned int             difficulte;
    std::string              motADeviner;
    std::string              motMasque;
    std::string              lettresUtilisees;
    bool                     victoire;

  public:
    Pendu();
    ~Pendu();

    std::string selectionnerFichier(unsigned int theme);
    void        definirMot(unsigned int theme, unsigned int difficulte);
    bool        estDeLaBonneTaille(unsigned int       difficulte,
                                   std::string        motADeviner,
                                   const unsigned int nombreCaracteresMaxFacile,
                                   const unsigned int nombreCaracteresMaxMoyen);
    void        masquerMot();
    void        menu();
    void        jouer();
    bool        estUneLettreValide(char lettre);
    void        remplacerLettre(char lettre);
    bool        estFinie() const;
    bool        aGagne(std::string motADeviner, std::string motMasque) const;
    void        reinitialiserPendu();
};

#endif
