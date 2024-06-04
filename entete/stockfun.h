#ifndef STOCKFUN_H
#define STOCKFUN_H
#include "structNoeud.h"


extern int isChem(char *chem);
extern int isChemAbs(char *chem);
extern noeud *listeContains(char *name, noeud *nd);
extern unsigned countFils(noeud *nd);
extern void afficheFils(noeud *nd);
extern char *sansDernierSlash(char *st);
extern int estSousArbre(noeud *racine, noeud *tmp);
extern bool hasSlash(char *st);
extern char *avantDernierSlash(char *chem);
extern unsigned nomLibre(noeud* pere, char* Newnom);
extern unsigned nomCorrect(char* nom);


#endif