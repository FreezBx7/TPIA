#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include <stdlib.h>
typedef struct _noeud
{
    int val; // valeur stockee
    struct _noeud * frere, * enfant; // pointeurs vers les noeuds
} NOEUD, * Arbre ;


int taille(Arbre noeud);
int hauteur(Arbre noeud);
Arbre creerNoeud(int n);
Arbre insererEnfant(Arbre racine,int n);
Arbre insererFrere(Arbre racine,int n);
void afficherAbre(Arbre a);

#endif // IA_H_INCLUDED
