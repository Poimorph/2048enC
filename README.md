# 2048enC

## Description
2048enC est une implémentation en C du célèbre jeu 2048 avec une interface graphique SDL2. Le jeu propose trois modes différents : classique, duo et puzzle, offrant une expérience de jeu variée et enrichissante.

Ce projet a été réalisé dans le cadre de l'UE IF2 (Algorithmique et Programmation) à l'Université de Technologie de Belfort-Montbéliard (UTBM).

---

## Modes de Jeu

### 1. Mode Classique
- Jeu traditionnel 2048 sur une grille unique
- Interface graphique
- Sauvegarde et reprise automatique de la partie
- Taille de grille personnalisable (4x4 à 9x9)

### 2. Mode Duo
- Jouez simultanément sur deux grilles côte à côte
- Score combiné des deux grilles
- Même mouvement appliqué aux deux grilles en même temps
- Interface graphique optimisée pour l'affichage double grille
- Taille de grille personnalisable (4x4 à 9x9)

### 3. Mode Puzzle
- Mode spécial avec des cases bloquées (représentées visuellement)
- Possibilité de charger une configuration prédéfinie
- Option pour générer aléatoirement un nouveau puzzle
- Interface visuelle adaptée au mode puzzle

---

## Commandes de Jeu
- Flèches directionnelles ou ZQSD pour déplacer les tuiles :
  - ↑ ou Z : Déplacer vers le haut
  - ↓ ou S : Déplacer vers le bas
  - ← ou Q : Déplacer vers la gauche
  - → ou D : Déplacer vers la droite
- Échap ou A : Quitter la partie (sauvegarde automatique)

## Installation

### Prérequis
- GCC (GNU Compiler Collection)
- Make
- SDL2 et SDL2_ttf
- Système d'exploitation compatible (Linux/Unix)

### Installation des dépendances

#### Sur Ubuntu/Debian :
```bash
sudo apt-get install gcc make libsdl2-dev libsdl2-ttf-dev
```

### Compilation et Lancement
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

### Commandes Make
- `make` : Compile le projet
- `make clean` : Nettoie les fichiers compilés
- `make mrpropre` : Nettoie les fichiers compilés et les sauvegardes

## Structure du Projet

### Fichiers Sources
- `src/main.c` : Point d'entrée du programme et gestion de la fenêtre SDL
- `src/game_logic.c` : Logique de base du jeu (déplacements, fusions...)
- `src/game_mode.c` : Implémentation des différents modes de jeu
- `src/display.c` : Gestion de l'affichage SDL
- `src/save_load.c` : Système de sauvegarde et chargement
- `src/functions.h` : Déclarations des fonctions et structures

### Ressources
- `resources/font.ttf` : Police de caractères pour l'interface
- `Puzzle/` : Dossier contenant les configurations de puzzle
- `saves/` : Dossier créé automatiquement pour les sauvegardes

## Fonctionnalités Techniques

### Interface Graphique
- Rendu SDL2
- Couleurs distinctes pour chaque valeur de tuile
- Affichage du score en temps réel
- Menu de sélection de mode et de taille
- Écran de game over avec score final

### Système de Jeu
- Gestion des collisions et fusions de nombres
- Génération aléatoire de nouvelles tuiles (2 ou 4)
- Détection automatique de fin de partie
- Support de plusieurs tailles de grille
- Obstacles fixes en mode puzzle

### Système de Sauvegarde
- Sauvegarde automatique en quittant
- Reprise de partie sauvegardée
- Sauvegarde distincte pour chaque mode et taille
- Gestion des fichiers de sauvegarde par mode

## Notes de Développement
- Interface utilisateur développée avec SDL2 et SDL2_ttf
- Gestion de la mémoire optimisée
- Code modulaire et bien structuré
- Support des événements SDL pour les contrôles
- Système de couleurs dynamique pour les tuiles

## Auteurs
Ce projet a été réalisé par :
- Matteo Di Giorgio (matteo.di-giorgio@utbm.fr)
- Alexis Chassery (alexis.chassery@utbm.fr)
- Suhayb Saleh (suhayb.saleh@utbm.fr)

## Contexte
Projet réalisé dans le cadre de l'UE IF2B à l'UTBM (Université de Technologie de Belfort-Montbéliard).
