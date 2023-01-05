#ifndef IHMPENDU_H
#define IHMPENDU_H

#include <string>
#include "Pendu.h"

class IHMPendu
{
  private:
    std::string lettresDevinees;
    std::string lettresUtilisees;

  public:
    IHMPendu();
    ~IHMPendu();

    void afficherRegles();
    void afficherInfos();
    void nomUtilisateur();
    void entrerUneLettre();
    void afficherMot();
    void afficherPendu(unsigned int echecs);
    void afficherResume();
};

#endif