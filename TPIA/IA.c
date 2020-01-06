#include "IA.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

int taille(Arbre noeud)
{
    Arbre enfant;
    int compteur = 1;
    for (enfant = noeud->enfant; enfant != NULL; enfant = enfant->frere)
        compteur += taille(enfant);
    return compteur;
}

int hauteur(Arbre a){
    int h = 0;
    if(!a) h =1;
    else{
        printf("ok");
        h=1+hauteur(a->enfant);
    }


    return h;
}

Arbre creerNoeud(int n){

    Arbre a = NULL;
    a = (Arbre)malloc(sizeof(NOEUD));
    a->val = n;
    a->frere = a->enfant = NULL;
    return a;
}
Arbre insererEnfant(Arbre racine,int n){

if(!racine){
   return creerNoeud(n);
}
else
    racine->enfant = insererEnfant(racine->enfant,n);
    return racine;
}
Arbre insererFrere(Arbre racine,int n){

if(!racine)
    return creerNoeud(n);
else
    racine->frere = insererFrere(racine->frere,n);
    return racine;
}

void afficherArbre(Arbre a){
    if(a){
        afficherArbre(a->frere);
        printf(" %d ",a->val);
        afficherArbre(a->enfant);
    }
}