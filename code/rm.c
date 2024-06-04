#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "../entete/structNoeud.h"
#include "../entete/rm.h"
#include "../entete/pwd.h"
#include "../entete/cd.h"

void rmRecursif(noeud* nd); 

void rm(noeud* nd, char* chemin){

    //noeud a supp:
    noeud* aSup = cd(chemin, nd) ;
    if(aSup == NULL){
        printf("Le noeud a supprimer n'existe pas");
        exit(1);
    }

    // verifier que le noeud à supprimer n'est pas au dessus du noeud courant:
    noeud* parent = nd ;
    while(parent != nd->racine){
        if (parent == aSup){
            puts("Le noeud a supprimer est au dessus du repertoire courant !");
            exit(EXIT_FAILURE);
        }
        parent = parent -> pere ;
    }

    // recupérer le pére du noeud à suuprimer 
    noeud* pere = aSup->pere ;

    // test si le dossier à supprimer n'est pas la racine :
    if (aSup == nd->racine){
        puts("Le noeud a supprimer est la racine !");
        exit(EXIT_FAILURE);
    }

    // liste du pere :
    liste_noeud* avant = pere -> fils ;
    liste_noeud* listeASup ;


    // cas ou nd est le premeier élément de la liste :
    if (avant->no == aSup){
        listeASup = pere->fils ;
        pere->fils = avant->succ ; // le remplace par l'élément juste apres lui dans la liste 
    
    }else{
        //cherche l'element jsute avant aSup dans la liste:
        while(avant->succ-> no != aSup) avant = avant -> succ ;
        listeASup = avant->succ ;
        avant-> succ = avant-> succ ->succ ;// mets à jours le successeur
    }

    // supprimer le listeNoeud :
    free(listeASup) ;

    // lance la suppression en cascade:
    rmRecursif(aSup) ;

    return ;
}

void rmRecursif(noeud* nd){

    // s'occupe d'appeler tout les sous dosiers 
    if (nd->est_dossier){
        liste_noeud* act = nd->fils ;
        liste_noeud* temp ;
        while(act != NULL){
            temp = act ;
            rmRecursif(act->no) ; //appelle la destruction de ses fils avant sa propre destruction
            act = act-> succ ;
            free(temp) ; // nettoie la mémoire pour le liste noeud associé
        }
    }

    //nettoie la mémoire pour un noeud
    free(nd);
}

void rmTree(noeud* nd){
    rmRecursif(nd->racine) ;
}