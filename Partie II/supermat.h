#ifndef SUPERMAT_H
#define SUPERMAT_H

typedef int iQt;

typedef struct {
    iQt nl;
    iQt nc;
    double** ligne;
} SuperMatrixDescriptor;

typedef SuperMatrixDescriptor* SUPERMRT;

SUPERMRT allouerSupermat(iQt Ql, iQt Qc);
#define acces(a, i, j) ((a)->ligne[i][j])
SUPERMRT superProduit(SUPERMRT a, SUPERMRT b);
void permuterLignes(SUPERMRT a, iQt i, iQt j);
SUPERMRT sousMatrice(SUPERMRT a, iQt L1, iQt L2, iQt c1, iQt c2);
SUPERMRT matSupermat(double *m, iQt Qld, iQt Qcd, iQt Qle, iQt Qce);
void supermatMat(SUPERMRT sm, double *m, iQt Qld, iQt Qcd);
iQt contiguite(SUPERMRT a);
void rendreSupermat(SUPERMRT sm);

#endif