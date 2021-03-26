# Tests d'implémentations d'opérations vectorielles en assembleur

Ce programme permet de tester différentes implémentations en assembleur d'opérations sur les vecteurs. Ces implémentations utilisent les jeux d'instructions SSE, AVX et AVX2, rien n'a été conçu pour s'assurer que ces jeux sont présents à l'assemblage.
Ce programme n'a pas pour objectif d'être implémenté dans des logiciels plus importants, les optimisations du compilateur étant presque toujours meilleures. Ce programme est ainsi fournit tel quel, sans assurance de son fonctionnement.



## Compilation

Le programme peut être compilé en utilisant directement le Makefile, la compilation fonctionne avec g++ et a été testée sous Linux et Windows (avec MSYS2 et MinGW).



## Assembleur

Les parties de code en assembleur utilisent la syntaxe AT&T, syntaxe par défaut sous g++.



## Opérations implémentées :
 - Addition de deux vecteurs