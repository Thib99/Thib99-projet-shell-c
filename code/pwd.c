#include <stdio.h>
#include "../entete/pwd.h" 
#include "../entete/structNoeud.h" 

void pwdRec(noeud* nd) ;

void pwd(noeud* nd){
    printf("/");
    pwdRec(nd->pere);
    printf("%s", nd->nom) ;
    printf("\n") ;// retour à la ligne 
}

void pwdRec(noeud* nd){
    if (nd->racine != nd){
        pwdRec(nd->pere) ;
        printf("%s/", nd->nom) ;
    };
}