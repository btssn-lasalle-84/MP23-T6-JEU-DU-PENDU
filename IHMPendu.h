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
    void afficherInfos();
    void afficherMot(std::string motMasque);
    void afficherResume();

    std::string saisirNomUtilisateur();
    char        entrerUneLettre();
};

#endif