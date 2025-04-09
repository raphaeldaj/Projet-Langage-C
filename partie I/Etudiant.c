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

void SaisieEtudiants(){
    printf("Nombre d'etudiants (<=100) : ");
    scanf("%d", &NBETU);
    for(int i = 0; i < NBETU; i++){
        printf("Etudiant %d:\n", i+1);
        printf("Numero : ");
        scanf("%d", &VETU[i].numero);
        printf("Nom : ");
        scanf("%s", VETU[i].nom);
        printf("Note : ");
        scanf("%f", &VETU[i].note);
    }
}

// void AjouterEtudiant() {
//     if (NBETU < MAX) {
//         printf("Nouvel etudiant :\n");
//         printf("Numero : "); scanf("%d", &VETU[NBETU].numero);
//         printf("Nom : "); scanf("%s", VETU[NBETU].nom);
//         printf("Note : "); scanf("%f", &VETU[NBETU].note);
//         NBETU++;
//         ChainageParMerite();
//     } else {
//         printf("Capacite maximale atteinte !\n");
//     }
// }

// void AjouterEtudiant(){
//     if(NBETU < MAX){
//         printf("Nouvel etudiant :\n");
        
//         int num;
//         int numeroExiste;
//         do{
//             numeroExiste = 0;
//             printf("Numero : \n"); 
//             scanf("%d", &num);
            
//             for(int i = 0; i < NBETU; i++){
//                 if(VETU[i].numero == num){
//                     printf("Ce numero existe deja pour l'etudiant %s !\n", VETU[i].nom);
//                     numeroExiste = 1;
//                 }
//             }
//         }while(numeroExiste);
        
//         VETU[NBETU].numero = num;
//         printf("Nom : \n"); scanf("%s", VETU[NBETU].nom);
//         printf("Note : \n"); scanf("%f", &VETU[NBETU].note);
//         NBETU++;
//         ChainageParMerite();
//         printf("Etudiant ajoute avec succes !\n");
//     }else{
//         printf("Capacite maximale atteinte !\n");
//     }
// }

void AjouterEtudiant() {
    if (NBETU < MAX) {
        printf("Nouvel etudiant :\n");
        
        int num;
        int numeroExiste;
        do {
            numeroExiste = 0;
            printf("Numero : \n"); 
            scanf("%d", &num);
            
            for (int i = 0; i < NBETU; i++) {
                if (VETU[i].numero == num) {
                    printf("Ce numero existe deja pour l'etudiant %s !\n", VETU[i].nom);
                    numeroExiste = 1;
                }
            }
            while (getchar() != '\n');
        } while (numeroExiste);
        
        VETU[NBETU].numero = num;
        
        printf("Nom : \n");
        fgets(VETU[NBETU].nom, sizeof(VETU[NBETU].nom), stdin);
        VETU[NBETU].nom[strcspn(VETU[NBETU].nom, "\n")] = '\0';
        
        printf("Note : \n");
        scanf("%f", &VETU[NBETU].note);
        while (getchar() != '\n');
        
        NBETU++;
        ChainageParMerite();
        printf("Etudiant ajoute avec succes !\n");
    } else {
        printf("Capacite maximale atteinte !\n");
    }
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
    printf(" ----------------------------------------- -------------- \n");
    while(i != -1){
        printf("|%40s |(Note: %2.2f) |\n", VETU[i].nom, VETU[i].note);
        i = SUIVANT[i];
    }
    printf(" ----------------------------------------- -------------- \n");
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
    printf(" ----------------------------------------- -------------- \n");
    for (int i = 0; i < NBETU; i++) {
        printf("|%40s |(Note: %2.2f) |\n", etudiantTries[i].nom, etudiantTries[i].note);
    }
    printf(" ----------------------------------------- -------------- \n");
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
    printf(" ----------------------------------------- -------------- \n");
    for (int i = 0; i < NBETU; i++) {
        printf("|%40s |(Note: %2.2f) |\n", VETU[indices[i]].nom, VETU[indices[i]].note);
    }
    printf(" ----------------------------------------- -------------- \n");
}