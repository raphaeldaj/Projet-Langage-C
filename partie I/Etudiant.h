#ifndef ETUDIANT_H
#define ETUDIANT_H

#define MAX 100

typedef struct {
    int numero;
    char nom[50];
    float note;
} Etudiant;

extern Etudiant VETU[MAX];
extern int SUIVANT[MAX];
extern int DEB, NBETU;

void ChainageParMerite();
void SaisieEtudiants();
void AjouterEtudiant();
void SupprimerEtudiant(int num);
void Sauvegarder();
void Restaurer();
void AfficherParMerite();
void AfficherParAlpha();
void AfficherParAleatoire();

#include "etudiant.c"

#endif