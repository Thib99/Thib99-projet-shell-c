#include <string.h> 
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../entete/structNoeud.h"
#include "../entete/mkdir.h"
#include "../entete/stockfun.h"
#include "../entete/touch.h"

void ajoutElement(noeud* pere, char* Newnom, bool dossier) ;

void mkdir(noeud* nd, char* nomNewDir){
    ajoutElement(nd, nomNewDir, true) ;
}
void touch(noeud* nd, char* nomNewDir){
    ajoutElement(nd, nomNewDir, false) ;
}


void ajoutElement(noeud* pere, char* Newnom, bool dossier){

    if ( ! nomCorrect(Newnom)){
        exit(EXIT_FAILURE) ;
    }

    liste_noeud* next = pere -> fils  ;
    // test si le nom est deja present:
    if (! nomLibre(pere, Newnom)) {
        exit(EXIT_FAILURE) ;
    }
    

    // creation du nouveau element
    noeud* newElement  = malloc(sizeof(noeud)) ;
    newElement->est_dossier = dossier;
    newElement->pere = pere ;
    newElement->racine = pere->racine;
    newElement->fils = NULL ;
    strcpy(newElement->nom, Newnom) ;

    // creation de son liste noeud associer dans son pere:
    liste_noeud* newElementList = malloc(sizeof(liste_noeud)) ;
    newElementList->no = newElement ;

    // mets le nouvelle élément au devant de la liste 
    if (pere->fils == NULL){
        pere->fils  = newElementList ;
        newElementList -> succ = NULL ;
    }else{
        liste_noeud *tmp = pere->fils;
        while(tmp->succ != NULL){
            tmp = tmp->succ;
        }
        tmp->succ = newElementList;
        newElementList->succ = NULL ;
    }
}