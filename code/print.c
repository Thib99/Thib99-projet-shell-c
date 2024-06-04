#include<stdio.h>
#include<stdlib.h>
#include "../entete/structNoeud.h" 
#include "../entete/print.h"
#include "../entete/stockfun.h"

void printRM(noeud*nd, unsigned depth);

void print(noeud*nd){
    printRM(nd->racine, 0) ;
}

void printRM(noeud*nd, unsigned depth){
    
    for (int i = 0 ; i < depth; i++){
        printf("   ");
    }

    noeud *courant = nd;
    printf("Noeud ");
    if(courant == nd->racine){
        printf("/ ");
    }else{
        printf("%s ",courant->nom);
    }

    if(courant->est_dossier){
        printf("(D), ");
    }else{
        printf("(F), ");
    }

    if(courant!=nd->racine){
        if(courant->pere == nd->racine){
            printf("pere : /, ");
        }else{
            printf("pere : %s, ",courant->pere->nom);
        }
    }
    
    printf("%d fils : ",countFils(courant));
    afficheFils(courant);
    printf("\n");


    liste_noeud *tmp = nd->fils;
    ++depth ;
    while(tmp != NULL){
        printRM(tmp->no, depth);
        tmp = tmp->succ;
    }
}

void printFromRacine(noeud *nd){
    print(nd->racine);
};
