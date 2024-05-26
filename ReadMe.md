
# CER-J-O Management

**CER-J-O Management** est un programme codé en langage C qui permet à un entraîneur de consulter et analyser les performances de ses athlètes. L'entraîneur pourra notamment saisir de nouvelles performances et les analyser grâce à des outils de statistiques avancées.

## Pré-requis

**Langage:** C

**Bibliothèques:** stdio.h, stdlib.h, string.h, unistd.h, sys/ioctl.h, errno.h, float.h, ctype.h, stdbool.h et dirent.h


## Guide d’installation 

Pour compiler et lancer le projet, utiliser ceci dans votre terminal :

1 - **Compiler le programme**
```bash
  gcc -o main main.c functions.c file.c -I.
```
2 - **Executer le programme**
```bash
./main
```
## Fonctionnalité

1. **Ajouter un nouvel athlète**
  - Permet d'ajouter un nouvel athlète avec un nom unique. Si un athlète avec ce nom existe déjà, une alerte sera affichée.

2. **Ajouter une performance pour un athlète**
  - Permet d'ajouter une nouvelle performance (date, type d'épreuve, temps et position relais si applicable) pour un athlète existant.

3. **Afficher les statistiques des athlètes**
  - Rechercher les statistiques des athlètes par nom, date ou type d'épreuve.

4. **Afficher l'historique des performances d'un athlète**
   - Affiche l'historique complet des performances pour un athlète donné.

5. **Comparer les performances d'un athlète entre deux dates**
  - Compare et affiche la différence de performance d'un athlète entre deux dates spécifiées pour une épreuve donnée.

6. **Calculer les statistiques pour un athlète dans une épreuve**
  - Affiche le meilleur, le pire et le temps moyen pour une épreuve donnée d'un athlète.

7. **Trouver les meilleurs athlètes pour une épreuve**
  - Affiche les trois meilleurs athlètes pour une épreuve donnée basée sur les temps moyens de performance.




## Guide d'utilisation

1. **Lancer le programme**
  - Après avoir exécuté `./main`, vous serez présenté avec un menu principal où vous pouvez choisir différentes actions, telles que gérer les athlètes, ajouter des performances, et consulter les statistiques.

2. **Naviguer dans le menu**
  - Utilisez les numéros correspondant aux options de menu pour naviguer dans les différentes fonctionnalités du programme.

3. **Ajouter un nouvel athlète**
  - Sélectionnez l'option pour ajouter un nouvel athlète, puis entrez le nom de l'athlète.

4. **Ajouter une performance**
  - Sélectionnez l'option pour ajouter une performance, puis entrez le nom de l'athlète et les détails de la performance.

5. **Afficher les statistiques**
  - Sélectionnez l'option pour afficher les statistiques, puis choisissez le critère de recherche (nom, date ou type d'épreuve) et entrez les informations nécessaires.

6. **Comparer les performances**
  - Sélectionnez l'option pour comparer les performances, entrez le nom de l'athlète, l'épreuve et les deux dates à comparer.
   
## Fichiers

**Voici une explication des fichiers liée à un athlète :**

<img width="328" alt="Capture d’écran 2024-05-26 à 03 25 41" src="https://github.com/jkengineer42/CER-J-OManagement/assets/167258198/7c14f8b5-9370-4a25-894f-9465c5a8591d">


    1. La première ligne représente le nom de l'athlète.

    2. La deuxième ligne représente le nombre de performances enregistrées

    3. Les lignes suivantes représente les caractérisitque des performances, respectivement : 
    La date de la performance, le type d'épreuve, le temps en secondes, et enfin la position du relais, si l'épreuve n'est pas un relais, alors 0 est écrit.
## Erreurs

Voici une liste d'erreurs lors de l'utilisation du programme, prenez en compte avant le lancement du programme pour être avertis des problèmes que vous allez sûrement rencontrer.
## Auteurs

- [@KUGANESAN Arun](https://www.github.com/)
- [@KONDA-MOUGNONGUI Jérémie](https://www.github.com/jkengineer42)
- [@BOUHOU Haytham](https://www.github.com/HAYTHAM2005)



