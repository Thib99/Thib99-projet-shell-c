#include <stdio.h>
#include "../entete/structNoeud.h"
#include "../entete/ls.h"

void ls(noeud* nd){
    liste_noeud* suivant  = nd->fils ;
    puts("*") ;
    while(suivant != NULL){
        printf("%s",suivant->no->nom) ;
        printf("   ");
        if (suivant->no->est_dossier) printf("(d)");
        else printf("(f)");
        printf("\n") ;
        suivant = suivant->succ ;
    }
}