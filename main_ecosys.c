#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"

//Projet : Simulation d'un ecosysteme
//ESSABRI YOUNESS 28705780
//RICK GAO

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;


int main(void) {
    srand(time(NULL));

    // A completer. Part 2:

    //exercice 4, questions 2 et 4
  
    /*
    Animal *a=creer_animal(19,15,0);
    afficher_ecosys(a,NULL);
    bouger_animaux(a);
    afficher_ecosys(a,NULL);
    */
  
    /*
    reproduce(&a,1);
    afficher_ecosys(a,NULL);
    */

    //Exercice 5 question 2
    //Declaration du tableau monde de taille SIZE_X*SIZE_Y
    int monde[SIZE_X][SIZE_Y];
    
    /*
    Animal *lp=NULL;
    for(int i=0;i<20;i++)
    {
        ajouter_animal((int)(rand()%(SIZE_X-1))+1,(int)(rand()%(SIZE_Y-1))+1, rand()%5, &lp);
    }
    afficher_ecosys(lp,NULL);
    Animal *tmp=lp;
    //Visualisation de l'energie de chaque proie creer
    int cpt=0; //compteur de proies
    while(tmp)
    {
        printf("Energie Proie %d: %f\n",++cpt,tmp->energie);
        tmp=tmp->suivant;
    }
    //sleep(5);
    cpt=0;
    printf("---------ETAT ECOSYSTEME AVANT APPLICATION DE LA BOUCLE-------------\n");
    while(lp)
    {
        rafraichir_proies(&lp,monde); 
        afficher_ecosys(lp,NULL);
        tmp=lp;
        printf("ETAT ENERGIE:\n");
        while(tmp)
        {
            printf("Energie Proie %d : %f\n",++cpt,tmp->energie);
            tmp=tmp->suivant;
        }
        printf("-------------------------------------------------------\n");
        cpt=0;
        //usleep prend en parametre le temps en microseconde
        //sleep(3); //sleep prend en parametre un temps de pause en seconde
    }
    */


    //exercice 6, question 2
    /*
    Animal *lpredateur=NULL;
    Animal *lp=NULL;
    Animal *tmp=NULL;
    int cpt;
    for(int i=0;i<20;i++)
    {
        ajouter_animal((int)(rand()%(SIZE_X-1))+1,(int)(rand()%(SIZE_Y-1))+1, rand()%5, &lpredateur);
    }
    afficher_ecosys(lpredateur,NULL);
    tmp=lpredateur;
    //Visualisation de l'energie de chaque predateurs creer
    cpt=0; //compteur de predateurs
    while(tmp)
    {
        printf("Energie Predateur %d: %f\n",++cpt,tmp->energie);
        tmp=tmp->suivant;
    }
    //sleep(5);
    cpt=0;
    printf("---------ETAT ECOSYSTEME AVANT APPLICATION DE LA BOUCLE-------------\n");
    while(lpredateur)
    {
        rafraichir_predateurs(&lpredateur,&lp); 
        afficher_ecosys(lpredateur,NULL);
        tmp=lpredateur;
        printf("ETAT ENERGIE:\n");
        while(tmp)
        {
            printf("Energie Predateur %d : %f\n",++cpt,tmp->energie);
            tmp=tmp->suivant;
        }
        printf("-------------------------------------------------------\n");
        cpt=0;
        //usleep prend en parametre le temps en microseconde
        //sleep(5); //sleep prend en parametre un temps de pause en seconde
    }
    */
    
    //exercice 7, question 1
    //Initialisation de chaque case de monde à 0
    for(int i=0; i<SIZE_X;i++)
    {
        for(int j=0;j<SIZE_Y;j++)
        {
            monde[i][j]=0;
        }
    }

    //exercice 6, question 3
    Animal *lproie=NULL;
    Animal *lpredateur=NULL;
    Animal *tmp_pred=NULL;
    Animal *tmp_proie=NULL;
    int nb_proie=0; //Va contenir le nombre de proie au moment de l'iteration i
    int nb_predateur=0; //Va contenir le nombre de predateur au moment de l'iteration i
    FILE *f=fopen("Evol_Pop.txt","w");
    if(f==NULL)
    {
        printf("Erreur d'ouverture du fichier ! \n");
        exit(0);
    }
    int i=0;//Compteur d'iteration de boucle pour l'ecriture du fichier

    for(int j=0;j<20;j++)
    {
        ajouter_animal((int)(rand()%(SIZE_X-1))+1,(int)(rand()%(SIZE_Y-1))+1, 20, &lpredateur);
        ajouter_animal((int)(rand()%(SIZE_X-1))+1,(int)(rand()%(SIZE_Y-1))+1, 20, &lproie);
    }

    afficher_ecosys(lproie,lpredateur);
    sleep(2);
    fprintf(f,"%d %d %d\n",i,nb_proie,nb_predateur);
    while(lproie && lpredateur)
    { 
        rafraichir_monde(monde);
        rafraichir_proies(&lproie,monde);
        rafraichir_predateurs(&lpredateur,&lproie); 
        afficher_ecosys(lproie,lpredateur);
        //usleep prend en parametre le temps en microseconde
        //sleep(1); //sleep prend en parametre un temps de pause en seconde
        nb_proie=compte_animal_it(lproie);
        nb_predateur=compte_animal_it(lpredateur);
        fprintf(f,"%d %d %d\n",i,nb_proie,nb_predateur);
        i++;
    }
    fclose(f);
    //Dans le cas ou il resterait des proies ou des predateurs, il faudrait les liberer
    if(lpredateur)
    {
        printf("Les PREDATEURS ont gagné !\n");
        lpredateur=liberer_liste_animaux(lpredateur);
    }
    else
    {
        if(lproie)
        {
            printf("Les PROIES ont gagné !\n");
            lproie=liberer_liste_animaux(lproie);
        }
        else
        {
            printf("Il y'a EGALITE !\n");
        }
    }

    //exercice 7, question 3


    //exercice 8, question 1

    /*Apres avoir modifier le programme afin qui créer un fichier "Evol_Pop.txt" organiser de cette facon: num_iteration nb_proies nb_predateur
    Ouverture de gnuplut dans le terminal.
    Taper les commande :
        plot "Evol_Pop.txt" using 1:2 with lines title "proies"
        replot "Evol_Pop.txt" using 1:3 with lines title "predateurs" 
    
    */
    /*Diagnostic de l'observation du graphique obtenue:
    Les proies augmentent ce qui augmentent le nombre de predateur.
    A un moment, le nombre tres élevés de predateur entraine une diminution des proies qui a son tour provoque la diminution de predateur.
    Ce cycle ce répete jusqu'a ce qu'il n'y ait plus de predateurs
    */

    return 0;
    }

