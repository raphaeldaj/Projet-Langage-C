#include "etudiant.h"
#include <stdio.h>

int main() {
    Restaurer();
    int choix;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Supprimer un etudiant\n");
        printf("3. Afficher par merite\n");
        printf("4. Afficher par ordre alphabetique\n");
        printf("5. Afficher en ordre aleatoire\n");
        printf("6. Sauvegarder et quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                AjouterEtudiant(); 
                break;
            }
            case 2: {
                int numeroASupprimer;
                printf("Numero a supprimer : ");
                scanf("%d", &numeroASupprimer);
                SupprimerEtudiant(numeroASupprimer);
                break;
            }
            case 3: {
                AfficherParMerite(); 
                break;
            }
            case 4: {
                AfficherParAlpha();
                break;
            }
            case 5: {
                AfficherParAleatoire();
                break;
            }
            case 6: {
                Sauvegarder();
                break;
            }
            default: printf("Option invalide.\n");
        }
    } while (choix != 6);

    return 0;
}