#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ecosys.h"



//Ensemble du projet à soumettre debut seance 4
/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  //assert(x>0 && x<SIZE_X);
  //assert(y>0 && y<SIZE_Y);
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) 
{
  assert(x>0 && x<SIZE_X);
  assert(y>0 && y<SIZE_Y);
  Animal *tmp=creer_animal(x,y,energie);
  assert(tmp);//Verifier que l'animal à bien etait creer
  if(!(*liste_animal))
  {
    *liste_animal=tmp;
  }
  else
  {
    *liste_animal=ajouter_en_tete_animal(*liste_animal,tmp);
  }
} 

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) 
{
  Animal *tmp=(*liste);
  Animal *tmp2=NULL;
  if((*liste)==animal)
  {
    *liste=(*liste)->suivant;
    free(tmp);
    return;
  }
  while(tmp)
  {
    tmp2=tmp->suivant;
    if(tmp2 && tmp2==animal)
    {
      tmp->suivant=tmp2->suivant;
      free(tmp2);
      return ;
    }
    tmp=tmp->suivant;
  }  
  return ;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
    
    Animal *tmp=liste;
    while(liste)
    {
      liste=liste->suivant;
      free(tmp);
      tmp=liste;
    }
    return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }
  
  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
  float p_ch_dir=0.01;
    while(la)
    {
      if((rand()/(float)RAND_MAX)<=p_ch_dir)//Va changer de direction dans p_ch_dir pourcent des cas
      {
        la->dir[0]=(rand()%(3)-1); //Nouvelle direction dx generer aleatoirement entre [-1,1]
        la->dir[1]=(rand()%(3)-1); //Nouvelle direction dy generer aleatoirement entre [-1,1]
      }
      //Deplacement de l'animal

      la->x=((la->x+la->dir[0])+SIZE_X)%SIZE_X;
      la->y=((la->y+la->dir[1])+SIZE_Y)%SIZE_Y;
      /* l'ajout de SIZE_X permet de gerer le cas: x ou y serait negatif. 
      Le modulo SIZE_X permet de gerer le cas: x ou y serait superieur ou egale a SIZE_X ou SIZE_Y */

      la=la->suivant;
    }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *tmp=(*liste_animal);
  int i=0; //Compteur de reproduction
  while(tmp)
  {
    if((rand()/(float)RAND_MAX)<=p_reproduce)//Reproduction et creation d'un nouvelle animal dans p_repoduce pourcent des cas
    {
      (*liste_animal)=ajouter_en_tete_animal(*liste_animal,creer_animal(tmp->x,tmp->y,(tmp->energie)/2)); //nouvelle animal a la meme position que son parent avec une energie egale a la moitié de celle de son parent.
      tmp->energie=(tmp->energie)/2;//energie du parent divisé par 2.
      i++;//Compteur de reproduction incréménter de 1
    }
    tmp=tmp->suivant;
  }
}

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) 
{
    Animal *lproie_tmp=(*liste_proie);
    Animal *tmp; //Va nous permettre de stocker la proie lors de la supression
    bouger_animaux(*liste_proie);
    while(lproie_tmp)
    {
        lproie_tmp->energie=lproie_tmp->energie-1;
        if(lproie_tmp->energie<0)
        {
            tmp=lproie_tmp->suivant;
            enlever_animal(liste_proie,lproie_tmp);
            lproie_tmp=tmp;
        }
        else
        {
            if(monde[lproie_tmp->x][lproie_tmp->y]>0)
            {
                lproie_tmp->energie=lproie_tmp->energie+monde[lproie_tmp->x][lproie_tmp->y];
                monde[lproie_tmp->x][lproie_tmp->y]=-15;
            }
            lproie_tmp=lproie_tmp->suivant;
        }
    }
    reproduce(liste_proie,p_reproduce_proie);
}



/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) 
{
    while(l)
    {
        if(l->x==x && l->y==y)
        {
            return l;
        }
        l=l->suivant;
    }

    return NULL;
} 


/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) 
{
    Animal *proie_tmp;//Va permettre de stocker la proie trouver en x y (si elle existe)
    Animal *lpredateur_tmp=(*liste_predateur);
    Animal *tmp; //Va nous permettre de stocker le predateur lors de la supression
    bouger_animaux(*liste_predateur);
    while(lpredateur_tmp)
    {
        lpredateur_tmp->energie=lpredateur_tmp->energie-1;
        proie_tmp=animal_en_XY(*liste_proie,lpredateur_tmp->x,lpredateur_tmp->y);
        if(proie_tmp)
        {
            lpredateur_tmp->energie=lpredateur_tmp->energie+proie_tmp->energie;
            enlever_animal(liste_proie,proie_tmp);
        }
        if(lpredateur_tmp->energie<0)
        {
            tmp=lpredateur_tmp->suivant;
            enlever_animal(liste_predateur,lpredateur_tmp);
            lpredateur_tmp=tmp;
        }
        else
        {
            lpredateur_tmp=lpredateur_tmp->suivant;
        }
    }
    reproduce(liste_predateur,p_reproduce_predateur);
}



/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y])
{
    for(int i=0; i<SIZE_X;i++)
    {
        for(int j=0;j<SIZE_Y;j++)
        {
            monde[i][j]+=1;
        }
    }
}



void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur, Animal *liste_proie)
{
	FILE *f=fopen(nom_fichier, "w");
	if(f==NULL)
	{
		printf("ERREUR D'OUVERTURE DU FICHIER\n");
		return;
	}
	
	fprintf(f,"<proies>\n");
	while(liste_proie)
	{
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%.6f\n",liste_proie->x, liste_proie->y,liste_proie->dir[0],liste_proie->dir[1],liste_proie->energie);
		liste_proie=liste_proie->suivant;
	}
	fprintf(f,"</proies>\n");
	fprintf(f,"<predateurs>\n");
	while(liste_predateur)
	{
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%.6f\n",liste_predateur->x, liste_predateur->y,liste_predateur->dir[0],liste_predateur->dir[1],liste_predateur->energie);
		liste_predateur=liste_predateur->suivant;
	}
	fprintf(f,"</predateurs>\n");
	fclose(f);
		
}

void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie)
{
	FILE *f=fopen(nom_fichier, "r");
	if(f==NULL)
	{
		printf("ERREUR D'OUVERTURE DU FICHIER\n");
		return;
	}
	
	char buffer[256];
	fgets(buffer,256,f); //<proies> 
	fgets(buffer,256,f);
	int x_res,y_res;
	float e_res;
	int dir_res[2];
	while(strncmp(buffer,"</proies>",9)!=0)
	{
		sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f\n",&x_res,&y_res,dir_res,&dir_res[1],&e_res);
		ajouter_animal(x_res,y_res,e_res,liste_proie);
		(*liste_proie)->dir[0]=dir_res[0];
		(*liste_proie)->dir[1]=dir_res[1];
		fgets(buffer,256,f);
	} 
	fgets(buffer,256,f);//<predateurs>
	fgets(buffer,256,f);
	while(strncmp(buffer,"</predateurs>",13)!=0)
	{
		sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f\n",&x_res,&y_res,dir_res,&dir_res[1],&e_res);
		ajouter_animal(x_res,y_res,e_res,liste_predateur);
		(*liste_predateur)->dir[0]=dir_res[0];
		(*liste_predateur)->dir[1]=dir_res[1];
		fgets(buffer,256,f);
	}
	fclose(f); 
}