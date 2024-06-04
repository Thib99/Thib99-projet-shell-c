// include général:
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// include perso
#include "../entete/structNoeud.h"
#include "../entete/ls.h"
#include "../entete/rm.h"
#include "../entete/mkdir.h"
#include "../entete/pwd.h"
#include "../entete/touch.h"
#include "../entete/cd.h"
#include "../entete/print.h"
#include "../entete/mv.h"
#include "../entete/cp.h"
#include "../entete/shell.h"


void freeDecoupeEspace(char** p);
char **cutSpace(char *cmd);

noeud* act ;

void commande(char* cmd, unsigned numeroLigne){

    // parser les cmd en fonction des espaces :
    char** cmdSplit =  cutSpace(cmd) ;
    // char* nbrArgs = *(cmdSplit+3) ;
    char* token = *(cmdSplit) ;
    //   *(res+3) = malloc(2*sizeof(char));
    // char* premierligne = *ret ;

    unsigned nbrArgu = 0;
    for(int i = 1 ; i < 3 ; i++){
        if (*(cmdSplit+i) != NULL) nbrArgu++ ;
    }
    

    if (! strcmp(token, "ls")){
        if (nbrArgu != 0){
            puts("ls : Le nombre d' arguments n'est pas bon (0 attendu)") ;
            printf("Erreur à la ligne %d :\n%s\n", cmd, numeroLigne) ;
            exit(0) ;
        }
        ls(act) ;
        printf("\n");

    }else if ( ! strcmp(token, "rm")){
        if (nbrArgu != 1){
            puts("rm : Le nombre d' arguments n'est pas bon (1 attendu)") ;
            printf("Erreur à la ligne %d :\n%s\n", cmd, numeroLigne) ;
            exit(0) ;
        }
        rm(act, *(cmdSplit+1) ) ;

    }else if (! strcmp(token, "pwd")){
        if (nbrArgu != 0){
            puts("pwd : Le nombre d' arguments n'est pas bon (0 attendu)") ;
            printf("Erreur à la ligne %d :\n%s\n", cmd, numeroLigne) ;
            exit(0) ;
        }
        pwd(act) ;
        printf("\n");

    }else if ( !strcmp(token, "touch")){
        if (nbrArgu != 1){
            puts("touch : Le nombre d' arguments n'est pas bon (1 attendu)") ;
            printf("Erreur à la ligne %d :\n%s\n", cmd, numeroLigne) ;
            exit(0) ;
        }
        touch(act, *(cmdSplit+1)) ;

    }else if (! strcmp(token, "mkdir")){
        if (nbrArgu != 1){
            puts("mkdir : Le nombre d' arguments n'est pas bon (1 attendu)") ;
            printf("Erreur à la ligne %d :\n%s\n", cmd, numeroLigne) ;
            exit(0) ;
        }
        mkdir(act, *(cmdSplit+1)) ;

    }else if ( ! strcmp(token, "cp")){
        if (nbrArgu != 2){
            puts("cp : Le nombre d' arguments n'est pas bon (2 attendu)") ;
            printf("Erreur à la ligne %d :\n%s\n", cmd, numeroLigne) ;
            exit(0) ;
        }
        cp(act, *(cmdSplit+1), *(cmdSplit+2)) ;

    }else if ( ! strcmp(token, "mv")){
        if (nbrArgu != 2){
            puts("mv : Le nombre d' arguments n'est pas bon (2 attendu)") ;
            printf("Erreur à la ligne %d :\n%s\n", cmd, numeroLigne) ;
            exit(0) ;
        }
        mv(act, *(cmdSplit+1), *(cmdSplit+2)) ;

    }else if ( ! strcmp(token, "cd")){
        if (nbrArgu != 1 && nbrArgu != 0){
            puts("cd : Le nombre d' arguments n'est pas bon (0 ou 1 attendu)") ;
            printf("Erreur à la ligne %d :\n%s\n", cmd, numeroLigne) ;
            exit(0) ;
        }
        act = cdDossier(*(cmdSplit+1), act) ;

    }else if (! strcmp(token, "print")){
        if (nbrArgu != 0){
            puts("print : Le nombre d' arguments n'est pas bon (0 attendu)") ;
            printf("Erreur à la ligne %d :\n%s\n", cmd, numeroLigne) ;
            exit(0) ;
        }
        print(act) ;
        printf("\n");
    
    }else{
        // commande non connu
        printf("Erreur cette commande est inconue :\n%s", cmd) ;
        exit(0) ;
    }
    

    //nettoyage de la memoire pour cmdSplit
    freeDecoupeEspace(cmdSplit);
}

void lectureFichier(const char* nom){
    FILE* fichier = fopen(nom, "r");
    char cmd[200] ;
    int len ;
    unsigned numeroLigne = 1 ;

    if (fichier != NULL){

        while(fgets(cmd, 200, fichier) != NULL){
            len = strlen(cmd);
            if (len==2 || len==1) continue ; //passe les lignes vides

            // prendre en compte le /n /r :
            if (len>=2 && (cmd[len-2] == '\r' || cmd[len-2] == '\n') ) cmd[len-2] = '\0';
            else if ( cmd[len-1] == '\n' || cmd[len-1] == '\r') cmd[len-1] = '\0';
            commande(cmd, numeroLigne++) ;
        }

        fclose(fichier) ;
    }else{
        printf("Le fichier %s est introuvable.", nom);
    }

    
}

void saisiclavier(){
    char cmd[200] ;
    int len ;
    while (1){

        scanf("%[^\n]", cmd) ; //lis l'entrée jusqu'au caractere \n
        len = strlen(cmd);
        fgetc( stdin ) ;

        if( ! strcmp("exit", cmd)) break ; // quitte le programe si l'utilsateur tape "exit"
        commande(cmd, 0) ;
    }
}


char **cutSpace(char *cmd){
    char **res = malloc(sizeof(char*)*3);
    char *cpy = malloc(sizeof(char)*(strlen(cmd)+1));
    *(res) = NULL;
    *(res+1) = NULL;
    *(res+2) = NULL;
    strcpy(cpy,cmd);
    char *tmp = strtok(cpy," ");
    if(tmp == NULL){
        puts("La ligne de commande est vide");
        exit(1);
    }
    *(res) = malloc(sizeof(char)*(strlen(tmp)+1));
    strcpy(*(res),tmp);
    tmp = strtok(NULL," ");
    if(tmp == NULL){
        free(cpy);
        return res;
    }
    *(res+1) = malloc(sizeof(char)*(strlen(tmp)+1));
    strcpy(*(res+1),tmp);
    tmp = strtok(NULL," ");
    if(tmp == NULL){
        free(cpy);
        return res;
    }
    *(res+2) = malloc(sizeof(char)*(strlen(tmp)+1));
    strcpy(*(res+2),tmp);
    tmp = strtok(NULL," ");
    if(tmp != NULL){
        puts("La ligne a trop d'arguments");
        exit(1);
    }
    free(cpy);
    return res;
    
}

void freeDecoupeEspace(char** p){
    free(*(p));
    free(*(p+1));
    free(*(p+2));
    free(p) ;
}

