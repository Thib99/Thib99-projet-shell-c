# Projet de C L2

## Groupe 61

Composé de :
- **Thibault Poux**
- **Lukas Tabouri**

---

### Compilation du projet

Pour compiler le projet, exécutez la commande suivante :
   
    make all

    
### Exécution du projet

#### Sur Windows :

    ./projet.exe NomFichierTexte


#### Sur Linux :

    ./projet NomFichierTexte


### Lancer le projet directement

Pour lancer le projet sans compilation explicite, utilisez la commande :

    make run


### Informations supplémentaires

- Les fichiers pouvant être exécutés doivent être placés dans le dossier **Test**. Pour les utiliser, il suffit de préciser le nom du fichier.
- Toutes les commandes du **MAKEFILE** sont adaptées à la fois pour Linux et Windows.
- Si le programme est exécuté sans arguments, l'utilisateur pourra entrer des commandes directement dans le terminal. Pour quitter le shell, il suffira de taper **"exit"**.
- Pour vérifier que le programme gère correctement la mémoire sans créer de fuite mémoire, utilisez Valgrind (sur Linux) avec la commande suivante :
    ```bash
    make vg
    ```



