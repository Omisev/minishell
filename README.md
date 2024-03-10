# **Projet minishell**

<div align="center">
  <img src="https://github.com/ayogun/42-project-badges/raw/main/badges/minishelle.png" alt="Badge du projet minishell">
</div>

##
<div align="center">
  <img src="https://github.com/Omisev/minishell/blob/main/Capture_minishell.png" alt="Capture d'écran de minishell">
</div>

## Description
Ce projet a pour but de créer une version simplifiée du shell Unix. Cela inclut l'interprétation des commandes, la gestion de l'environnement, ainsi que l'exécution de commandes externes.

## Tableau des Composants du Projet

| Fichier              | Description                                                              | Responsabilité                                   | Statut    |
|----------------------|--------------------------------------------------------------------------|--------------------------------------------------|-----------|
| `main.c`             | Fichier principal, contient la logique de haut niveau                    | Initialisation, boucle d'interprétation          | Complet   |
| `parser.c`           | Analyse les commandes entrées par l'utilisateur                          | Parsing de commandes                             | Complet   |
| `executor.c`         | Exécute les commandes analysées                                           | Exécution de commandes                           | Complet   |
| `env_manager.c`      | Gère les variables d'environnement                                        | Manipulation de l'environnement                  | Complet   |
| `builtin_commands.c` | Implémente les commandes internes du shell (ex : cd, echo)               | Commandes internes                               | Complet   |
| `utils.c`            | Fonctions utilitaires                                                     | Fonctions auxiliaires                            | Complet   |
| `Makefile`           | Fichier pour compiler le projet                                           | Compilation                                      | Complet   |
| `minishell.h`        | Fichier d'en-tête contenant les déclarations et les macros               | Déclarations                                     | Complet   |

## Installation et Compilation
git clone git@github.com:Omisev/minishell.git

cd minishell

make

./minishell

## Utilisation

## Options
Aucune option disponible pour ce projet.

## Caractéristiques
- Interprétation des commandes
- Gestion des variables d'environnement
- Exécution de commandes externes
- Implémentation de commandes internes
- Gestion des signaux

## Fonctions externes autorisées
- malloc
- free
- read
- write
- open
- close
- fork
- execve
- wait
- waitpid
- signal

## Ressources utilisées
- [Notions essentielles du shell bash](https://fr.wikibooks.org/wiki/Programmation_Bash/Notions_essentielles_du_shell_bash)
- [Liste des séquences d'échappement ANSI](https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences)
- [Appel système fork](https://www.geeksforgeeks.org/fork-system-call/)

