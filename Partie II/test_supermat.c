#include <stdio.h>
#include "supermat.h"
#include "supermat.c"

void afficherMatrice(SUPERMRT sm) {
    if (!sm) {
        printf("Matrice NULL\n");
        return;
    }
    
    for (iQt i = 0; i < sm->nl; i++) {
        for (iQt j = 0; j < sm->nc; j++) {
            printf("%6.2f ", acces(sm, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

int main() {

    printf("Test d'allocation\n\n");
    SUPERMRT a = allouerSupermat(3, 2);
    if (!a) {
        printf("Échec d'allocation de a \n");
        return 1;
    }
    
    for (iQt i = 0; i < a->nl; i++) {
        for (iQt j = 0; j < a->nc; j++) {
            acces(a, i, j) = i * a->nc + j + 1; //initialiser de 1 a (i fois j +1)
        }
    }

    afficherMatrice(a);
    
    printf("Test de produit matriciel\n\n");

    SUPERMRT b = allouerSupermat(2, 4);

    if (!b) {
        printf("Échec d'allocation de b pour le produit matriciel \n");
        return 1;
    }

    for (iQt i = 0; i < b->nl; i++) {
        for (iQt j = 0; j < b->nc; j++) {
            acces(b, i, j) = i * b->nc + j + 1;
        }
    }
    afficherMatrice(b);

    printf("la premierre matrice \n\n");
    afficherMatrice(a);
    printf("la deuxieme matrice \n\n");
    afficherMatrice(b);
    
    printf("resultat du produit \n\n");
    SUPERMRT c = superProduit(a, b);
    afficherMatrice(c);
    
    printf("Test de permutation de lignes\n\n");
    printf("Avant permutation:\n\n");
    afficherMatrice(a);
    permuterLignes(a, 0, 1);
    printf("Apres permutation des lignes 0 et 1:\n\n");
    afficherMatrice(a);
    
    printf("Test de sous-matrice\n\n");
    printf("matrice d'origine\n\n");
    SUPERMRT sous = sousMatrice(c, 1, 2, 1, 3);
    afficherMatrice(c);
    printf("sous-matrice extraite\n\n");
    afficherMatrice(sous);
    
    printf("Test de conversion matrice en supermatrice\n\n");
    double mat[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    SUPERMRT sm = matSupermat(&mat[0][0], 3, 4, 3, 4);
    afficherMatrice(sm);
    
    printf("Test de conversion supermatrice en matrice\n\n");
    double mat2[3][4] = {0};
    supermatMat(sm, &mat2[0][0], 3, 4);
    for (iQt i = 0; i < 3; i++) {
        for (iQt j = 0; j < 4; j++) {
            printf("%6.2f ", mat2[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    printf("Test de contiguite\n\n");
    printf("Contiguite de a: %d\n", contiguite(a));
    printf("Contiguite de sm: %d\n", contiguite(sm));
    
    rendreSupermat(a);
    rendreSupermat(b);
    rendreSupermat(c);
    rendreSupermat(sous);
    rendreSupermat(sm);
    
    return 0;
}