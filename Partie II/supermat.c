#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "supermat.h"

SUPERMRT allouerSupermat(iQt Ql, iQt Qc) {
    if (Ql <= 0 || Qc <= 0){
        return NULL;
    }
    
    SUPERMRT sm = (SUPERMRT)malloc(sizeof(SuperMatrixDescriptor));
    if (!sm){
        return NULL;
    }
    
    sm->nl = Ql;
    sm->nc = Qc;
    
    sm->ligne = (double**)malloc(Ql * sizeof(double*));
    if (!sm->ligne){
        free(sm);
        return NULL;
    }
    
    for (iQt i = 0; i < Ql; i++) {
        sm->ligne[i] = (double*)malloc(Qc * sizeof(double));
        if (!sm->ligne[i]) {
            for (iQt j = 0; j < i; j++) free(sm->ligne[j]);
            free(sm->ligne);
            free(sm);
            return NULL;
        }
    }
    
    return sm;
}

SUPERMRT superProduit(SUPERMRT a, SUPERMRT b) {
    if (!a || !b || a->nc != b->nl){
        return NULL;
    }
    
    iQt nl = a->nl;
    iQt nc = b->nc;
    iQt nk = a->nc;// ou on peut aussi mettre b->nl vue que le nombe de ligne de a doit etre aussi le nombre de colone de b
    
    SUPERMRT result = allouerSupermat(nl, nc);
    if (!result){
        return NULL;
    }
    
    for (iQt i = 0; i < nl; i++) {
        for (iQt j = 0; j < nc; j++) {
            double sum = 0.0;
            for (iQt k = 0; k < nk; k++) {
                sum += acces(a, i, k) * acces(b, k, j);
            }
            acces(result, i, j) = sum;
        }
    }
    
    return result;
}



void permuterLignes(SUPERMRT a, iQt i, iQt j) {
    if (!a || i < 0 || j < 0 || i >= a->nl || j >= a->nl){
        return;
    }
    
    double* temp = a->ligne[i];
    a->ligne[i] = a->ligne[j];
    a->ligne[j] = temp;
}



SUPERMRT sousMatrice(SUPERMRT a, iQt L1, iQt L2, iQt c1, iQt c2) {
    if (!a || L1 < 0 || L2 >= a->nl || c1 < 0 || c2 >= a->nc || L1 > L2 || c1 > c2){
        return NULL;
    }
    
    iQt nl = L2 - L1 + 1;
    iQt nc = c2 - c1 + 1;
    
    SUPERMRT sm = (SUPERMRT)malloc(sizeof(SuperMatrixDescriptor));
    if (!sm){
        return NULL;
    }
    
    sm->nl = nl;
    sm->nc = nc;
    
    sm->ligne = (double**)malloc(nl * sizeof(double*));
    if (!sm->ligne) {
        free(sm);
        return NULL;
    }
    
    for (iQt i = 0; i < nl; i++) {
        sm->ligne[i] = a->ligne[L1 + i] + c1;
    }
    
    return sm;
}



SUPERMRT matSupermat(double *m, iQt Qld, iQt Qcd, iQt Qle, iQt Qce) {
    if (!m || Qle <= 0 || Qce <= 0 || Qle > Qld || Qce > Qcd){
        return NULL;
    }
    
    SUPERMRT sm = (SUPERMRT)malloc(sizeof(SuperMatrixDescriptor));
    if (!sm){
        return NULL;
    }
    
    sm->nl = Qle;
    sm->nc = Qce;
    
    sm->ligne = (double**)malloc(Qle * sizeof(double*));
    if (!sm->ligne) {
        free(sm);
        return NULL;
    }
    
    for (iQt i = 0; i < Qle; i++) {
        sm->ligne[i] = m + i * Qcd;
    }
    
    return sm;
}



void supermatMat(SUPERMRT sm, double *m, iQt Qld, iQt Qcd) {
    if (!sm || !m || sm->nl > Qld || sm->nc > Qcd){
        return;
    }
    
    for (iQt i = 0; i < sm->nl; i++) {
        for (iQt j = 0; j < sm->nc; j++) {
            m[i * Qcd + j] = acces(sm, i, j);
        }
    }
}



iQt contiguite(SUPERMRT a) {
    if (!a || !a->ligne || a->nl == 0 || a->nc == 0) return 0;
    
    int ordonne = 1;
    for (iQt i = 1; i < a->nl; i++) {
        if (a->ligne[i] != a->ligne[i-1] + a->nc) {
            ordonne = 0;
            break;
        }
    }
    
    if (ordonne) return 2;
    
    return 0;
} 



void rendreSupermat(SUPERMRT sm) {
    if (!sm){
        return;
    }
    
    if (sm->ligne) {
        for (iQt i = 0; i < sm->nl; i++) {
            if (sm->ligne[i]){
                free(sm->ligne[i]);
            }
        }
        free(sm->ligne);
    }
    
    free(sm);
}