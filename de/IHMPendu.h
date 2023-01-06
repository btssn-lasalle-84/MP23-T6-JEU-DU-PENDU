#ifndef IHMPENDU_H
#define IHMPENDU_H

#include <string>
#include "Pendu.h"

using namespace std;

class IHMPendu
{
  private:
    string lettresDevinees;
    string lettresUtilisees;

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
