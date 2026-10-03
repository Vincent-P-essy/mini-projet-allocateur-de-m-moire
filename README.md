
# Projet : Implémentation de my_malloc / my_free

##  Contexte

Ce projet a été réalisé dans le cadre du **TP 9 - Mini Projet II** d’Architecture des Systèmes Informatiques en L3 Informatique à l’Université Gustave Eiffel.

L’objectif était de **réimplémenter `malloc` et `free`** en langage C, mais en les faisant fonctionner **sur un segment statique de 1 Go** plutôt que via les fonctions standards de la glibc.

---

##  Fonctionnalités principales

- `void* my_malloc(size_t size)` : allocation d’un bloc mémoire.
- `void my_free(void* ptr)` : libération de la mémoire allouée.
- Allocation et libération gérées **via une liste chaînée de blocs mémoires** avec métadonnées.
- Optimisations :
  - Fusion des blocs libres adjacents.
  - Pointeur `last_free` pour améliorer les performances.
  - Alignement mémoire respecté.

---

##  Stratégie utilisée

Le pool mémoire statique est fragmenté en blocs avec une structure contenant les informations suivantes :
- Taille du bloc
- État (libre/occupé)
- Pointeurs `next` et `prev` (liste doublement chaînée)

Les blocs sont manipulés pour permettre l’allocation, la libération et la **fusion** lors des appels à `my_free`.

---

##  Arborescence du projet

```text
.
├── my_malloc.c
├── my_malloc.h
├── main.c
├── version_bien_commente_de_malloc.c
├── Makefile
└── README.md
```

---

## Compilation et exécution

```bash
make
./main
```

Le programme de test exerce l’allocation, la libération et la fusion de blocs.

##  Objectifs pédagogiques

- Compréhension du fonctionnement bas niveau de l’allocation mémoire.
- Manipulation avancée de pointeurs, structures et mémoire contiguë.
- Implémentation d’un allocateur simple, robuste, et partiellement optimisé.

---

##  Licence

Ce projet est publié à des fins **éducatives uniquement**. Toute réutilisation dans un cadre académique ou personnel est autorisée avec mention de l’auteur.

---

##  Auteur

Vincent Plessy  
GitHub : [Vincent-P-essy](https://github.com/Vincent-P-essy)
