#ifndef IHMPENDU_H
#define IHMPENDU_H

#include <string>
#include "Pendu.h"

class IHMPendu
{
  private:
    std::string lettresUtilisees;
    std::string lettresDevinees;

  public:
    IHMPendu();
    ~IHMPendu();

    void afficherRegles();
    void afficherPendu(unsigned int echecs);
    void afficherInfos(const unsigned int nombreEssaisMax,
                       unsigned int       echecs,
                       std::string        lettresUtilisees);
    void afficherMot(std::string motMasque);
    void afficherResume(unsigned int       echecs,
                        std::string        motADeviner,
                        bool               victoire,
                        const unsigned int nombreEssaisMax);

    std::string saisirNomUtilisateur();
    char        entrerUneLettre(char lettre);
    void        afficherErreurLettre();
    void        afficherErreurLettreDejaUtilisee();
};

#endif