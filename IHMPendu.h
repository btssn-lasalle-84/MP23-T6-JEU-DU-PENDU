#ifndef IHMPENDU_H
#define IHMPENDU_H

#include <string>
#include "Pendu.h"

#define VERSION               1.1
#define NB_LIGNE_DESSIN_PENDU 10

class IHMPendu
{
  private:
    std::string lettresUtilisees;
    std::string lettresDevinees;
    std::string nom;

  public:
    IHMPendu();
    ~IHMPendu();

    void afficherRegles(const unsigned int nombreEssaisMax) const;
    void afficherPendu(unsigned int echecs) const;
    void afficherInfos(const unsigned int nombreEssaisMax,
                       unsigned int       echecs,
                       std::string        lettresUtilisees) const;
    void afficherMot(std::string motMasque) const;
    void afficherResume(unsigned int       echecs,
                        std::string        motADeviner,
                        bool               victoire,
                        const unsigned int nombreEssaisMax) const;

    std::string saisirNomUtilisateur();
    char        entrerUneLettre(char lettre);
    void        afficherErreurLettre() const;
    void        afficherErreurLettreDejaUtilisee() const;
};

#endif