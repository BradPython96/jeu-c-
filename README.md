# ROBs VS Robots

## Rêgles du jeu

Deux amis se retrouve soudainement attaqué par des ordes de robots. Lorsqu'ils commencent ils n'ont pour se défendre qu'un simple pistolet laser. Par chance la carte dans laquelle ils se déplacent est jonchée de cadeau surprise cela peut leur permettre de récupérer de la vie ou encore ramasser des grenades ou des bazookas chargés. Les vagues s'enchainent sans fin avec a chaque tour de plus en plus de robot à vaincre. Jusqu'où serez-vous capable d'aller ?

## Installation

Pour pouvoir joueur au jeu ROBs VS Robots il est nécessaire de posséder :

- SFML 2.5 : https://www.sfml-dev.org/download-fr.php

## Lancement du jeu

Pour lancer le jeu il faut d'abord entrer la commande ``make`` dans le terminal pour compiler les fichiers, puis la commande ``./jeu`` pour executer le programme. Une nouvelle fenêtre va s'ouvrir, à partir de ce moment il vous faut suivre les étapes suivantes pour franchir les différents menus :

- Cliquez sur ``Enter`` pour démarer le jeu
- Le Joueur 1 choisit si il est une fille (tapez ``1``) ou un garçon (tapez ``2``)
- Le Joueur 2 choisit si il est une fille (tapez ``1``) ou un garçon (tapez ``2``)
- Selectionnez la map sur laquelle vous souhaitez jouer (tapez ``1`` ou ``2``)

### Selection du personnage

Le choix du personnage aura un impact simplement ésthétique pour la suite du jeu. Les deux personnages auront les mêmes armes et les mêmes avantages.

### Selection de la map

La map n°2 est une ébauche, pour profiter pleinement du jeu il est conseillé de jouer sur la map n°1.

## Commandes du jeu

### Diriger le Joueur 1

- ``Z`` : marcher vers le haut
- ``S`` : marcher vers le bas
- ``Q`` : marcher vers la gauche
- ``D`` : marcher vers la droite

- ``E`` : switcher d'arme
- ``Space`` : tirer

### Diriger le Joueur 2

- ``Flèche Haut`` : marcher vers le haut
- ``Flèche Bas`` : marcher vers le bas
- ``Flèche Gauche`` : marcher vers la gauche
- ``Flèche Droit`` : marcher vers la droite

- ``M`` : switcher d'arme
- ``L`` : tirer

### Ramasser un accessoire

Pour ramasser un cadeau au sol il suffit de se diriger vers celui-ci et il sera ramassé automatiquement.

## Fonctionnement du programme

### Comprendre le code en bref

La classe ``Game`` gère tout ce qui est relié à l'affichage : la gestion des fenêtres, l'actualisation de l'affichage à chaque tour, ainsi que la récupération des informations émisent par le clavier. 

Un attribut ``Map`` est inclue dans la classe ``Game``, c'est dans cette autre classe que vont être géré toutes les intéractions entre les éléments du jeu. En effet, cette classe ``Map`` contient deux ``Player`` ainsi qu'une liste de ``Robot`` et une d'``Accessoire``.

Les ``Player`` possèdent chacun une table statique d'``Arme`` et de ``Missile``. Individuellement ils s'occupe des missiles qu'ils ont tiré et des armes qu'ils possèdent.

### Les détails travaillés avec précision

Vous pourez constater que les classes ``Missile`` sont particulièrement travaillé. En effet, suivant l'arme utilisé l'impact est différent par exemple un simple pistolet laser ne va retirer des PVs qu'au premier robot touché par le laser. Au contraire, le Bazooka va avoir un effet destructeur plus important car il va infliger des dégats à tous les robots se trouvant dans la zone d'impact. Mais encore, la grenade va avoir un effet différent car elle va exploser a un endroit définit par sa portée et retirer des PVs à tous les robots se trouvant dans sa zone de dommage. De plus, l'affichage des explosions est particulièrement travaillé pour un meilleur gameplay.

Les déplacements des robots sont travaillés dans la classe ``Map``. Ils sont construit de sorte que les robots ne se superposent pas et que dans le cas ou ils se retrouveraient bloqués par l'un des leurs ils essayeront de détourner le problème pour se rapprocher toujours plus des ``Player``.

## Test

Différentes classes de tests ont été réalisé. Pour compiler ses tests entrée la commande ``make Test`` puis la commande ``./Test`` pour les executer.

## Auteurs

#### Simon Ferrier
#### Déborah Malexieux
#### ROB4
