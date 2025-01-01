# 2048enC

## Description
2048enC est une implémentation en langage C du célèbre jeu 2048. Le jeu propose trois modes différents : classique, duo et puzzle, offrant une expérience de jeu variée et enrichissante.

Ce projet a été réalisé dans le cadre de l'UE IF2 (Algorithmique et Programmation) à l'Université de Technologie de Belfort-Montbéliard (UTBM).

---

## Modes de Jeu

### 1. Mode Classique
- Jeu traditionnel 2048 sur une grille unique
- Possibilité de sauvegarder et reprendre la partie
- Taille de grille personnalisable (4x4 à 9x9)

### 2. Mode Duo
- Jouez simultanément sur deux grilles
- Score combiné des deux grilles
- Même mouvement appliqué aux deux grilles en même temps
- Taille de grille personnalisable (4x4 à 9x9)

### 3. Mode Puzzle
- Mode spécial avec des cases bloquées (représentées par 'X')
- Possibilité de charger une configuration prédéfinie depuis un fichier
- Option pour générer aléatoirement un nouveau puzzle
- Défi supplémentaire avec des obstacles fixes

---

## Commandes de Jeu
- Z : Déplacer vers le haut
- S : Déplacer vers le bas
- Q : Déplacer vers la gauche
- D : Déplacer vers la droite
- A : Quitter la partie

## Installation

### Prérequis
- GCC (GNU Compiler Collection)
- Make
- SDL

### Compilation
1. Clonez le dépôt :
```bash
git clone [url-du-repo]
cd 2048enC
```

2. Compilez le projet :
```bash
make
```

3. Lancez le jeu :
```bash
./2048
```

### Nettoyage
Pour nettoyer les fichiers compilés :
```bash
make clean
```

Pour nettoyer les fichiers compilés et les parties sauvegardées :
```bash
make mrpropre
```

## Structure des Fichiers
- `src/main.c` : Point d'entrée du programme
- `src/game_logic.c` : Logique de base du jeu (déplacements, fusions...)
- `src/game_mode.c` : Implémentation des différents modes (normal, duo, puzzle)
- `src/display.c` : Fonctions d'affichage
- `src/save_load.c` : Gestion des sauvegardes
- `src/functions.h` : Header file avec toutes les déclarations
- `Puzzle/` : Dossier contenant les puzzles prédéfinis
- `Puzzle/puzzleOne.txt` : Exemple de configuration de puzzle
- `saves/` : Dossier créé automatiquement pour les sauvegardes
- `Makefile` : Script de compilation

## Fonctionnalités
- Sauvegarde automatique en quittant
- Reprise de partie sauvegardée
- Affichage du score en temps réel
- Interface en console claire et intuitive
- Gestion des collisions et fusions de nombres
- Génération aléatoire de nouvelles tuiles (2 ou 4)
- Chargement de puzzles prédéfinis (mode puzzle)
- Génération aléatoire de nouveaux puzzles (mode puzzle)

## Règles du Jeu
1. Utilisez les touches ZQSD pour déplacer les tuiles
2. Deux tuiles de même valeur fusionnent en une tuile de valeur double
3. À chaque mouvement valide, une nouvelle tuile (2 ou 4) apparaît
4. Le but est d'atteindre la tuile 2048 (ou plus)
5. La partie se termine quand aucun mouvement n'est possible
6. En mode puzzle, les cases bloquées ('X') ne peuvent pas être déplacées

## Notes Techniques
- Les grilles sont représentées par des tableaux 2D
- Les cases vides sont représentées par des points (.)
- Les cases bloquées (mode puzzle) sont représentées par 'X'
- Le score augmente à chaque fusion et nouvelle tuile
- Les sauvegardes sont stockées dans des fichiers texte séparés pour chaque mode et taille de grille
- Les configurations de puzzles sont stockées dans des fichiers texte dans le dossier `Puzzle/`

## Auteurs
Ce projet a été réalisé par :
- Matteo Di Giorgio(matteo.di-giorgio@utbm.fr)
- Alexis Chassery (alexis.chassery@utbm.fr) 
- Suhayb Saleh (suhayb.saleh@utbm.fr)

## Contexte
Projet réalisé dans le cadre de l'UE IF2B à l'UTBM (Université de Technologie de Belfort-Montbéliard).
