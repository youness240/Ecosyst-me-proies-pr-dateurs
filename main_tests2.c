#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ecosys.h"

  float p_ch_dir=0.01;
  float p_reproduce_proie=0.4; 
  float p_reproduce_predateur=0.5;
  int temps_repousse_herbe=-15;

int main()
{
    srand(time(NULL));
    Animal *liste_predateur=NULL;
    Animal *liste_proies=NULL;
    int i;
    afficher_ecosys(liste_proies,liste_predateur);


    //Creation de 20 proies et 20 predateurs
    for(i=0;i<20;i++)
    {
        ajouter_animal((int)(rand()%(SIZE_X-1))+1,(int)(rand()%(SIZE_Y-1))+1, 0, &liste_predateur);
        ajouter_animal((int)(rand()%(SIZE_X-1))+1,(int)(rand()%(SIZE_Y-1))+1, 0, &liste_proies);
    }

    //Test de la fonction ecire_ecosys
    afficher_ecosys(liste_proies,liste_predateur);
    ecrire_ecosys("file.txt",liste_predateur,liste_proies);

    //Test de la fonction lire_ecosys
    Animal *liste_predateur_res=NULL;
    Animal *liste_proies_res=NULL;
    lire_ecosys("file.txt",&liste_predateur_res,&liste_proies_res);

    //Affichage de l'ecosysteme
    afficher_ecosys(liste_proies,liste_predateur);

    Animal *p=creer_animal(liste_proies->x, liste_proies->y,0);
    enlever_animal(&liste_proies,p);
    enlever_animal(&liste_predateur,liste_predateur->suivant);

    //Affichage de l'ecosysteme avec une proie et un predateur en moins
    afficher_ecosys(liste_proies,liste_predateur);

    //Liberation des listes
    liste_predateur=liberer_liste_animaux(liste_predateur);
    liste_proies=liberer_liste_animaux(liste_proies);
    free(p);
    //execution avec valgrind afin de verifier qu'aucune fuite memoire n'a eu lieu
    //Affichage de l'ecosysteme afin de verifier que plus aucun predateur et proie ne soit present
    afficher_ecosys(liste_proies,liste_predateur);

    return 0;   
}