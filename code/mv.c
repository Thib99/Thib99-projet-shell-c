#include <stdlib.h>
#include <stdio.h>

#include "../entete/structNoeud.h"
#include "../entete/stockfun.h"
#include "../entete/cd.h"
#include "../entete/mv.h"
#include "../entete/pwd.h"


void mv(noeud* nd, char *chem1, char *chem2){

    noeud* noeudADeplacer = cd (chem1, nd) ;
    char *chemSansDernierSlash = sansDernierSlash(chem2) ;
    char * nom = avantDernierSlash(chem2) ;
    noeud* repArriver = cd(chemSansDernierSlash, nd) ;

    // test si repArriver n'est pas un sous arbre de noeudADeplacer
    if ( estSousArbre(noeudADeplacer, repArriver)){
        puts("Le chemin de destination est un sous arbre du chemin de depart !");
        exit(1);
    }
    
    if ( ! nomCorrect(nom)){
        exit(EXIT_FAILURE) ;
    }

    liste_noeud* next = repArriver -> fils  ;
    // test si le nom est deja present:
    if (! nomLibre(repArriver, nom) ){
        puts("Il y a deja un fichier de ce nom dans ce repertoire !");
        exit(EXIT_FAILURE) ;
    }

    // Recherche la liste noedu correspondant au noedu à deplacer
    liste_noeud* avant = noeudADeplacer ->pere  -> fils ;
    liste_noeud* listeA_MV ;

    // cas ou nd est le premeier élément de la liste :
    if (avant->no == noeudADeplacer){
        listeA_MV = noeudADeplacer ->pere ->fils ;
        noeudADeplacer ->pere ->fils = avant->succ ; // le remplace par l'élément juste apres lui dans la liste 
    
    }else{
        //cherche l'element jsute avant Noeud A deplacer dans la liste:
        while(avant->succ-> no != noeudADeplacer) avant = avant -> succ ;
        listeA_MV = avant->succ ;
        avant-> succ = avant-> succ ->succ ;// mets à jours le successeur
    }


    listeA_MV -> succ = repArriver -> fils ;
    repArriver -> fils = listeA_MV ;

    //netoyer memoire des variables temporaires
    if (nom != NULL) free(nom);
    if (chemSansDernierSlash != NULL) free(chemSansDernierSlash);


}