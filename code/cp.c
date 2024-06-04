#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../entete/structNoeud.h"
#include "../entete/stockfun.h"
#include "../entete/cp.h"
#include "../entete/cd.h"
#include "../entete/mkdir.h"
#include "../entete/touch.h"

void copyFromTo(noeud *from, noeud *to, char *name){
    if(from->est_dossier){
        mkdir(to,name);
        liste_noeud *tmp = from->fils;
        noeud *tmp2 = cd(name,to);
        while(tmp != NULL){
            copyFromTo(tmp->no,tmp2,tmp->no->nom);
            tmp = tmp->succ;
        }
    }else{
        touch(to,name);
    }
}


void cp(noeud *nd, char *chem1, char *chem2){
    noeud *fromCopy = cd(chem1,nd);
    if(fromCopy == NULL){
        puts("Le fichier que vous essayez de copier n'existe pas !");
        exit(1);
    }
    char *chem2SansDernierSlash = sansDernierSlash(chem2);
    noeud *toCopy;
    if(strcmp(chem2SansDernierSlash,"") == 0){
        toCopy = cdRacine(nd) ; 
    }else{
        if(strcmp(chem2SansDernierSlash,"*") == 0){
            toCopy = nd;
        }else{
            toCopy = cd(chem2SansDernierSlash,nd);
        }
        
    }
    if(toCopy == NULL){
        puts("Le chemin de destination de la copie n'existe pas !");
        exit(1);
    }
    if(estSousArbre(fromCopy, toCopy)>=1){
        puts("Le chemin de destination est un sous arbre du chemin de départ !");
        exit(1);
    }
    char *newName = avantDernierSlash(chem2);     //ne pas oublier de free(newName)
    if(strlen(newName)>99){
        puts("Le nom de la copie est trop long");
        exit(1);
    }
    liste_noeud *tmp = toCopy->fils;
    
    while(tmp!=NULL){
        if(strcmp(tmp->no->nom,newName) == 0){
            printf("Le chemin de destination possede deja un dossier (ou fichier) nome : %s\n",newName);
            exit(1);
        }
        tmp = tmp->succ;
    }
    

    copyFromTo(fromCopy,toCopy,newName);

    
    //netoyer memoire des variables temporaires
    if (newName != NULL) free(newName);
    if (chem2SansDernierSlash != NULL) free(chem2SansDernierSlash);
    

}


