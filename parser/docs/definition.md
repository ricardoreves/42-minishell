## Voici les différentes étapes du parser

1) On rerçoit en entré une chaine de caractère qui représente la commande du
terminal a executé. 

2) La chaine de caractère va être découpé en jeton. Ces jetons représente tous
les mots que l'on retrouve dans la commande.

A partir de là, on va créer un arbre d'execution de la commande selon la
grammaire illustré sur le schéma suivant : [diagram](diagram.xhtml) *

Il est possible aussi de consulter La [grammaire au format EBNF](grammar.txt).




* Le diagramme a été généré avec l'outil en ligne 
[Railroad Diagram Generator](https://www.bottlecaps.de/rr/ui)


voir de la documentation sur 
[transpiler](https://www.mrcoder.org/fr/compiler/minijava/introduction/)
