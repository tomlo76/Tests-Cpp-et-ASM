# Tests d'implémentations d'opérations vectorielles en assembleur

Ce programme permet de tester différentes implémentations en assembleur d'opérations sur les vecteurs. Ces implémentations utilisent les jeux d'instructions SSE, AVX et AVX2, rien n'a été conçu pour s'assurer que ces jeux sont présents à l'assemblage.
Ce programme n'a pas pour objectif d'être implémenté dans des logiciels plus importants, les optimisations du compilateur étant presque toujours meilleures. Ce programme est ainsi fournit tel quel, sans assurance de son fonctionnement.



## Compilation

Le programme peut être compilé en utilisant directement le Makefile, la compilation fonctionne avec g++ et a été testée sous Linux et Windows (avec MSYS2 et MinGW).

Les codes avant assemblage peuvent être obtenus avec la commande `make asm`.



## Assembleur

Les parties de code en assembleur utilisent la syntaxe AT&T, syntaxe par défaut sous g++.



## Utilisation

Le programme permet de sélectionner le nombre de tours de boucle à réaliser avec l'option `-n` ou `-N`, suivie d'un nombre. Il permet aussi de sélectionner la ou les implémentation(s) à tester avec l'option `--mode` ou `-m`, les différents modes possibles sont `compiler`, `serial`, `sse`, `avx` et `all`.

En fonctionnement, le programme affiche une réalisation de l'opération pour chaque implémentation sélectionnée, ainsi que le temps de calcul pour le nombre d'opérations spécifié, le nombre d'opérations par seconde et le temps moyen d'une opération.



## Opérations implémentées :
 - Addition de deux vecteurs