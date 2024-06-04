#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../entete/structNoeud.h"
#include "../entete/cd.h"
#include "../entete/stockfun.h"

noeud *cdRacine(noeud *nd){
    return nd->racine;
}

noeud * cdDossier(char *st , noeud *nd){
    noeud* sortie = cd(st, nd);
    if (! sortie->est_dossier){
        puts("Attenion le cd pointe sur un fichier !") ;
        exit(0) ;
    }
    return sortie ;
}
noeud *cd(char *st , noeud *nd){

    if (st == NULL){ // pour "cd"
        return nd->racine ; 
    }
    if(! strcmp(st, "..")){ //pour "cd .."
        return nd->pere ;
    }

    if(isChem(st) == 0){
    return NULL;
    }

    if(isChemAbs(st) == 1){
        char *copie = malloc(sizeof(char)*(strlen(st)));
        strcpy(copie,st+1);
        noeud *courant = nd->racine;
        char *tmp =strtok(copie,"/");
        noeud *tmp2 = courant;
        while(tmp != NULL){
            tmp2 = listeContains(tmp, tmp2);
            if(tmp2 == NULL){break;}
            tmp = strtok(NULL,"/");
        }
        free(copie) ;
        return tmp2;
    }else{
        char *copie = malloc(sizeof(char)*(strlen(st)+1));
        strcpy(copie,st);
        noeud *courant = nd;
        char*tmp = strtok(copie,"/");
        noeud *tmp2 = courant;
        while(tmp != NULL){
            tmp2 = listeContains(tmp, tmp2);
            if(tmp2 == NULL){break;}
            tmp = strtok(NULL,"/");
        }
        free(copie) ;
        return tmp2;
    }
    
}