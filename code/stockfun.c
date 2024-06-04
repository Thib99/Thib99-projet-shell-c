#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../entete/structNoeud.h"



int isChem(char *chem){
    if(strlen(chem) == 0 || strcmp(chem, "/") == 0 || chem[strlen(chem)-1] == '/'){
        return 0;
    }
    return 1;
}

int isChemAbs(char *chem){
    if(chem[0] == '/'){
        return 1;
    }
    return 0;
}

noeud *listeContains(char *name, noeud *nd){
    liste_noeud *tmp = nd->fils;
    while(tmp != NULL){
        if(strcmp(tmp->no->nom,name) == 0){
            return tmp->no;
        }
        tmp = tmp->succ;
    }
    return NULL;
}

unsigned countFils(noeud *nd){
    unsigned res = 0;
    liste_noeud *courant = nd->fils;
    while(courant != NULL){
        res++;
        courant = courant->succ;
    }
    return res;
}

void afficheFils(noeud *nd){
    if(nd->fils != NULL){
        liste_noeud *courant = nd->fils;
        while(courant != NULL){
            printf("%s ",courant->no->nom);
            if(courant->no->est_dossier){
                printf("(D),");
            }else{
                printf("(F),");
            }
            courant = courant->succ;
        }
    }
}

bool hasSlash(char *st){
    for(size_t i = 0; i<strlen(st); i++){
        if(*(st+i) == '/'){
            return true;
        }
    }
    return false;
}

char *sansDernierSlash(char *st){
    if(!hasSlash(st)){
        char *res = malloc(sizeof(char)*2);
        *(res) = '*';
        *(res+1) = '\0';
        return res;
    }
    if(strlen(st)<=0){
        return NULL;
    }
    size_t cpt = 0;
    size_t i = strlen(st)-1;
    while(i>=0 && *(st+i) != '/'){
        //printf("cpt = %d, st+%d = %c \n",cpt,i,*(st+i));
        cpt++;
        i--;
    }
    cpt++;
    char *res = malloc(sizeof(char)*(strlen(st)-cpt+1));
    strncpy(res,st,strlen(st)-cpt);
    *(res + strlen(st)-cpt) = '\0';
    return res;
}

char *avantDernierSlash(char *chem){
    if(!hasSlash(chem)){
        char *res = malloc(sizeof(char)*(strlen(chem)+1));
        strcpy(res,chem);
        return res;
    }
    if(strlen(chem)<=0){
        return NULL;
    }
    size_t cpt = 0;
    size_t i = strlen(chem)-1;
    while(i>=0 && *(chem+i) != '/'){
        cpt++;
        i--;
    }
    char *res = malloc(sizeof(char)*(cpt+1));
    strncpy(res,chem+strlen(chem)-cpt,cpt);
    *(res+cpt) = '\0';
    return res;
    
}


int estSousArbre(noeud *racine, noeud *tmp){
    if(racine == NULL || tmp == NULL){
        puts("L'un des deux noeud (ou les deux) est NULL");
        exit(1);
    }
    if(racine == tmp){
        return 1;
    }
    if(racine->fils == NULL){
        return 0;
    }
    liste_noeud *tmp2 = racine->fils;
    int i = 0;
    while(tmp2 != NULL){
        i+= estSousArbre(tmp2->no,tmp);
        tmp2 = tmp2->succ;
    }
    return i;
}





unsigned nomCorrect(char* Newnom){
    // test si nom de fichier non vide, alphanumérique, et libre
    if ( ! strcmp(Newnom, "")){
        puts("Le nom du noeud est "" !");
        return 0 ;
    }
    if (  strlen(Newnom) > 99){
        puts("Le nom du noeud est trop long (max 99 char) !");
        return 0 ;
    }

    // regarde si tout les caratéres son alphanumerique
    char* lettre = Newnom ;
    while (*lettre != '\0')
    {
        if ( ! isalnum(*lettre)){
            puts("Certain caracteres du nom ne sont pas alphaNumerique !");
            return 0 ;
        }
        lettre +=1 ;
    }

    return 1 ;
}

unsigned nomLibre(noeud* pere, char* Newnom){
    // test si le nom est deja present:
    liste_noeud* next = pere -> fils  ;
    while(next != NULL ){
        if (! strcmp(next->no->nom, Newnom)){
            puts("Le nom est deja present dans ce repertoire !");
            return 0 ;
        }
        next = next->succ ;
    }

    return 1 ;
}