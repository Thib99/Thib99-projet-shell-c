#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "../entete/structNoeud.h"
#include "../entete/stockfun.h"
#include "../entete/shell.h"
#include "../entete/rm.h"
#include "../entete/print.h"
#include "../entete/mkdir.h"
#include "../entete/cd.h"
#include "../entete/ls.h"
#include "../entete/touch.h"
#include "../entete/pwd.h"
#include "../entete/cp.h"
#include "../entete/mv.h"

extern noeud* act ;

// attend en argument un le nom d'un fichier texte
int main(int argc, char const *argv[])
{

    // creation du noeud racine :
    noeud* racine = malloc(sizeof(noeud)) ;
    racine->est_dossier = true;
    racine->pere = racine ;
    racine->racine = racine;
    racine->fils = NULL ;
    racine->nom[0] = '\0' ;

    // attribution du noeud actuel
    act = racine ;


    if (argc == 2){
        char *tmp = malloc(sizeof(char)*(5+strlen(argv[1])+1));
        *(tmp) = 'T';
        *(tmp+1) = 'e';
        *(tmp+2) = 's';
        *(tmp+3) = 't';
        *(tmp+4) = '/';
        for(size_t i = 0; i<strlen(argv[1]); i++){
            *(tmp+5+i) = *(argv[1]+i);
        }
        *(tmp+5+strlen(argv[1])) = '\0';
        lectureFichier(tmp) ; // shell par rapport au fichier en argument
        free(tmp);
    }else{
        puts("Veuillez renseigner un nom de fichier en arguments,") ;
        puts ("si vous voulez que son arbre correspondant sois crée.") ;
        puts("Lancement du shell interactif !") ;
        saisiclavier();
    }


    // nettoyer tout l'arbre 
    rmTree(act) ;
   
    return 0;
}
