#ifndef IHMPENDU_H
#define IHMPENDU_H

#include <string>


using namespace std;


class IHMPendu 
{
  private:
   string lettresDevinees;
   string lettresUtilisees;

  public:
    IHMPendu();
    ~IHMPendu();

    void afficherRegles() const;
    void afficherInfos() const;
    void nomUtilisateur();
    void entrerUneLettre();
    void afficherMot() const;
    void afficherPendu(unsigned int echecs) const;
    void afficherResume() const;
};

#endif