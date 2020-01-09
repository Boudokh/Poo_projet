Euj Escape Game - EEG🚪💠🌟🏃👾👾👾
====================================

<p>
<details>
<summary> Projet C++ 2019/2020 - Langage à Objets Avancé - Université de Paris - Double Master Mathématiques, Informatique parcours Data Science (MIDS). <summary>

<details>
<p>
<summary> Tuteur : Jean-Baptiste Yunès (aka JBY). 

<details>
<p>
<summary> Réalisé par : Mohamed Boudokhane et Mohamed-Amine Bousahih.


Description du projet
---------------------

Ce projet a pour but de proposer la création d'un ensemble de deux applications écrites en langage C++ : une application de conception de plateaux de jeu et une application permettant de jouer sur un ensemble de plateaux. 

Le jeu est à temps discret directement piloté par l'utilisateur. Celui-ci déplace à l'aide d'un clavier un personnage afin d'aller récupérer un maximum de trésors tandis que des personnages hostiles automatisés tentent de l'en empêcher. 

Votre mission est la suivante : réussir à traverser tous les plateaux.


Attention : nos amis les streumons 👾 apprennent de leurs erreurs et deviennent de plus en plus intelligents ... 

Concepts de bases
-----------------

<details>
<p>
<summary> Un oueurj 🏃 symbolisé par le caractère J et qui peut se déplacer, à chaque tour, dans l'une des huits adjacentes (si possible), rester sur place ou se téléporter (voir après).

<details>
<p>
<summary> Des streumons 👾 symbolisés par le caractère s et qui peuvent se déplacer, à chaque tour, dans l'une des huits cases adjacentes (si possible). Un streumon n'a qu'un but dans la vie : dévorer le oueurj.

<details>
<p>
<summary> Des reumus symbolisés par X. Un reumu est inamovible et aucun élément ne peut le traverser ou monter dessus. C'est un obstacle parfait. Il y a tout autour du plateau des reumus ainsi qu'au moins une teupors (voir après).

<details>
<p>
<summary> Des diams 💠 symbolisés par le caractère $ qui peuvent être rammassés par le oueurj. Celui-ci doit d'ailleurs en ramasser au moins un avant qu'une porte de sortie ne s'ouvre et qu'il puisse tenter de s'y engouffrer. Les diams sont ignorés par les streumons.

<details>
<p>
<summary> Des geurchars 🌟 symbolisés par le caractère * et qui permettent d'obtenir, pour le oueurj, une possibilité de téléportation en plus et activable à volonté.

<details>
<p>
<summary> Des teupors 🚪 symbolisés par + si elles sont ouvertes et - si fermées. A chaque fois que le oueurj ramasse un diam une nouvelle teupor s'ouvre par laquelle le oueurj peut sortir du plateau.


Représentation d'un plateau
-------------------

(add un screen d'un plateau)


Commandes de bases 
--------------------

En tant qu'utilisateur, vous contrôlez le oueurj à travers ses déplacements :

- z : déplacement en haut.
- a : déplacement en haut diagonale gauche.
- e : déplacement en haut diagonale droite.
- d : déplacement à droite.
- q : déplacement à gauche.
- x : déplacement en bas.
- c : déplacement en bas diagonale droite.
- w : déplacement en bas diagonale gauche.
- s : arrêter le jeu.


Lorsque vous récupérez des geuchars 🌟 , vous avez la possibilité de vous téléportez (de manière infini) :

- t : téléportation aléatoire sur une position (i,j) du plateau.

Attention : dans certaines situations, vous remercierez votre ami le geuchar 🌟 de vous avoir sauvé des streumons 👾. Dans certains cas, il peut vous mettre dans des situations délicates ...

Extensions utiles 
-----------------

<details>
<p>
<summary>  Les streumons 👾 <summary>


Au cours de votre partie, vous aurez l'occasion de rencontrer différents types de streumons doués de plus ou moins d'intelligence :

- Type n°0 : ce sont des streumons qui ne sont pas allé à l'école des streumons quand ils étaient petit ... leurs déplacements sont aléatoires et ne tiennent pas en compte de la position du oueurj.

- Type n°1 : diplômés de l'école des streumons, ils appliquent l'algorithme A* à la perfection afin de rechercher le chemin le plus court afin de dévorer le oueurj !.

- Type n°2 : ce sont des streumons schizophrène qui passent de l'état "aléatoire" à l'état "A*" à tout moment. 


Lorsque les streumons se marchent dessus, différentes interactions sont possibles :

- L'élimination : si deux streumons se marchent dessus alors ils disparaissent.

- La reproduction : si deux streumons se marchent dessus alors ils disparaissenent et engendrent un baby streum ! (une sorte de reproduction comme les poissons ...).

- La création d'artefact : si deux streumons se marchent dessus alors ils disparaissent et engendrent un trésor (un diams 💠 ou un geuchar 🌟 ). Le oueurj 🏃 s'en réjouira ! 


<details>
<p>
<summary> Sauvegarder une partie   <summary>