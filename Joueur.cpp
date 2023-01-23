#include "Joueur.h"

#ifdef DEBUG_JOUEUR
#include <iostream>
#endif

using namespace std;

Joueur::Joueur()
{
#ifdef DEBUG_JOUEUR
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] " << this
              << std::endl;
#endif
}

Joueur::~Joueur()
{
#ifdef DEBUG_JOUEUR
    std::cout << "[" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "] " << this
              << std::endl;
#endif
}
