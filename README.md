# Moteur Physique

## Groupe 5 - Kiryu
* Amaury Mehlman
* David Ponton
* Clark Randall
* Pierre Teodoresco

## Compilation

Pour compiler le code il faut commencer par créer un projet en utilisant l'outil d'OpenFramework. Il est aussi possible d'utiliser un projet déjà existant.
Ensuite il faut ajouter l'ensemble des fichiers dans le dossier **src/**.
Il est aussi surement nécessaire d'ajouter les fichiers à la solution dans Visual Studio.

## Utilisation

Une fois dans l'application, pour effectuer un tir il faut, dans un premier temps, sélectionner un projectile.
Pour ce faire il faut utiliser les touches du clavier précisées à l'écran :
* **B** : pour un boulet de canon
* **F** : pour un ballon de football
* **P** : pour une balle de ping-pong

Quand une particule est sélectionée, son nom est affiché à côté de la mention **Selected**.
Une fois l'étape de sélection terminée, il suffit de cliquer avec sa souris pour choisir une vélocité initiale.
Le simulateur utilise le vecteur entre le coin inférieur gauche et l'emplacement du clique pour définir ce vecteur de vélocité initiale.

Phase 2:
Déplacer le blob avec A et D