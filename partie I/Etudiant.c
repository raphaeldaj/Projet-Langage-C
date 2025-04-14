#include "etudiant.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

Etudiant VETU[MAX];
int SUIVANT[MAX];
int DEB = -1, NBETU = 0;

void ChainageParMerite(){
    DEB = -1;
    for(int i = 0; i < NBETU; i++){
        SUIVANT[i] = -1;
    }

    for(int i = 0; i < NBETU; i++){
        if(DEB == -1){
            DEB = i;
        }else{
            if(VETU[i].note >= VETU[DEB].note){
                SUIVANT[i] = DEB;
                DEB = i;
            }else{
                int j = DEB;
                while (SUIVANT[j] != -1 && VETU[i].note < VETU[SUIVANT[j]].note) {
                    j = SUIVANT[j];
                }
                SUIVANT[i] = SUIVANT[j];
                SUIVANT[j] = i;
            }
        }
    }
}

void SaisieEtudiants() {
    if (NBETU < MAX) {
        printf("Nouvel etudiant :\n");
        
        // Saisie et vérification du numéro (inchangé)
        int num;
        int numeroTrouve;
        do {
            numeroTrouve = 0;
            printf("Numero : \n"); 
            scanf("%d", &num);
            
            for (int i = 0; i < NBETU; i++) {
                if (VETU[i].numero == num) {
                    printf("Ce numero existe deja pour l'etudiant %s !\n", VETU[i].nom);
                    numeroTrouve = 1;
                }
            }
            while (getchar() != '\n');
        } while (numeroTrouve);
        
        VETU[NBETU].numero = num;
        
        printf("Nom : \n");
        fgets(VETU[NBETU].nom, sizeof(VETU[NBETU].nom), stdin);
        VETU[NBETU].nom[strcspn(VETU[NBETU].nom, "\n")] = '\0';
        
        float note;
        int noteValide;
        do {
            noteValide = 1;
            printf("Note (entre 0 et 20) : \n");
            scanf("%f", &note);
            
            if (note < 0 || note > 20) {
                printf("Erreur : La note doit etre comprise entre 0 et 20.\n");
                noteValide = 0;
            }
            
            while (getchar() != '\n');
        } while (!noteValide);
        
        VETU[NBETU].note = note;
        
        printf("Etudiant ajoute avec succes !\n");
    } else {
        printf("Capacite maximale atteinte !\n");
    }
}

void AjouterEtudiant() {
    SaisieEtudiants();
    NBETU++;
    ChainageParMerite();
}

void SupprimerEtudiant(int num) {
    int j = -1;
    for (int i = 0; i < NBETU; i++) {
        if (VETU[i].numero == num) {
            j = i;
            break;
        }
    }

    if (j != -1) {
        for (int i = j; i < NBETU-1; i++) {
            VETU[i] = VETU[i+1];
        }
        NBETU--;
        ChainageParMerite();
    }else{
        printf("ce numero d'etudiant n'a pas ete trouve \n\n");
    }
}

void Sauvegarder() {
    FILE *f = fopen("etudiants.dat", "wb");
    if(f == NULL){
        printf("Erreur lors de l'ouverture du fichier !\n");
        return;
    }
    fwrite(VETU, sizeof(Etudiant), NBETU, f);
    fclose(f);
}

void Restaurer(){
    FILE *f = fopen("etudiants.dat", "rb");
    if(f == NULL){
        printf("Aucune donnee a restaurer !\n");
        return;
    }
    NBETU = fread(VETU, sizeof(Etudiant), MAX, f);
    fclose(f);
    ChainageParMerite();
}

void AfficherParMerite(){
    printf("\n=== Classement par merite ===\n \n");
    int i = DEB;
    printf(" ----------- ----------------------------------------- -------------- \n");
    while(i != -1){
        printf("| Num: %4d |%40s |(Note: %2.2f) |\n",VETU[i].numero, VETU[i].nom, VETU[i].note);
        i = SUIVANT[i];
    }
    printf(" ----------- ----------------------------------------- -------------- \n");
}

void AfficherParAlpha(){
    Etudiant etudiantTries[MAX];
    for (int i = 0; i < NBETU; i++){
        etudiantTries[i] = VETU[i];
    }

    for (int i = 0; i < NBETU-1; i++) {
        for (int j = i+1; j < NBETU; j++) {
            if (strcmp(etudiantTries[i].nom, etudiantTries[j].nom) > 0) {
                Etudiant temp = etudiantTries[i];
                etudiantTries[i] = etudiantTries[j];
                etudiantTries[j] = temp;
            }
        }
    }

    printf("\n=== Ordre alphabetique ===\n \n");
    printf(" ----------- ----------------------------------------- -------------- \n");
    for (int i = 0; i < NBETU; i++) {
        printf("| Num: %4d |%40s |(Note: %2.2f) |\n",etudiantTries[i].numero, etudiantTries[i].nom, etudiantTries[i].note);
    }
    printf(" ----------- ----------------------------------------- -------------- \n");
}

void AfficherParAleatoire() {
    int indices[MAX];

    for (int i = 0; i < NBETU; i++){
        indices[i] = i;
    }

    srand(time(NULL));
    for (int i = NBETU-1; i > 0; i--) {
        int j = rand() % (i+1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    printf("\n=== Ordre aleatoire ===\n \n");
    printf(" ----------- ----------------------------------------- -------------- \n");
    for (int i = 0; i < NBETU; i++) {
        printf("| Num: %4d |%40s |(Note: %2.2f) |\n",VETU[indices[i]].numero, VETU[indices[i]].nom, VETU[indices[i]].note);
    }
    printf(" ----------- ----------------------------------------- -------------- \n");
}