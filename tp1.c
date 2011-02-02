#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Fonctions de manipulation de matrices pleines

// definition de constantes globales
#define L 7 // Largeur de la matrice pleine
#define H 4 // Hauteur de la matrice pleine




// initialise une matrice pleine avec des entiers aleatoires
void init_pleine(int pleine[H][L])
{
    // initialisation du generateur de nombres aleatoires
    srand(time(NULL));
    for (unsigned l = 0; l < H; l++) {
        for (unsigned c = 0; c < L; c++) {
            // une facon de garantir qu'il y aura beaucoup de 0
            pleine[l][c] = (rand() % 19) - 9;
	    if (pleine[l][c] % 2 == 0) pleine[l][c] = 0;
	    //pleine[l][c] =  ; //l+c;
        }
    }
}

void init_pleine_constante(int pleine[H][L], int constante)
{
    // initialisation du generateur de nombres aleatoires
    srand(time(NULL));
    for (unsigned l = 0; l < H; l++) {
        for (unsigned c = 0; c < L; c++) {
	    pleine[l][c] = constante ; 
        }
    }
}
// affiche une matrice pleine
void affiche_pleine(int pleine[H][L])
{
    for (unsigned l = 0; l < H; l++) {
        for (unsigned c = 0; c < L; c++) {
            printf("%5d ", pleine[l][c]);
        }
        printf("\n");
    }
    printf("\n");
}





// Fonctions de manipulation de matrices creuses

// le type cellule
typedef struct cell_t {
    int val; // valeur de la cellule
    unsigned lig, col; // position de la cellule dans la matrice
    struct cell_t *suiv_lig, *suiv_col; // liens vers les cellules voisines
}cell_t;

// le type matrice creuse
typedef struct creuse_t {
    unsigned nbr_lig; // le nombre de lignes de la matrice
    struct cell_t **lignes; // tableau des lignes
    unsigned nbr_col; // le nombre de lignes de la matrice
    struct cell_t **colonnes; // tableau des colonnes
}creuse_t;


creuse_t* init_creuse()
{
    
    creuse_t* creuse = malloc(sizeof(creuse_t));
    creuse->nbr_lig = H;
    creuse->nbr_col = L;
    creuse->lignes = calloc(creuse->nbr_lig, sizeof(cell_t*));
    creuse->colonnes = calloc(creuse->nbr_col, sizeof(cell_t*));
    return creuse;
}
void liberer_liste(cell_t* liste) //, int* i)
{
    cell_t* a_supprimer;
    while(liste != NULL)
    {
	a_supprimer = liste;
	liste = liste->suiv_col;
	free(a_supprimer);
    }
}
void liberer_creuse(creuse_t* creuse)
{
    for (unsigned l = 0; l < H; l++) 
    {
	liberer_liste(creuse->lignes[l]);
    }
    free(creuse->lignes);
    free(creuse->colonnes);
    free(creuse);
}
void affiche_creuse(creuse_t* creuse) 
{
    cell_t* tmp;
    for (unsigned l = 0; l < H; l++)
    {
      tmp = creuse->lignes[l]; 
      for (unsigned c = 0; c < L; c++) 
      {
	  if (tmp == NULL || tmp->lig !=l || tmp->col !=c) 
	  {
	      printf("%5d ", 0);	      
	  }
	  else
	  {
	      printf("%5d ", tmp->val);
	      tmp = tmp->suiv_col;
	  }
      }
      printf("\n");   
    }
    printf("\n");   
}

void ajouteenqueue(cell_t* liste_cell, cell_t* p_cell, short col)
{
    cell_t* tmp = liste_cell;
	if (col)
	{
	    while (tmp->suiv_col != NULL)
	    {
		tmp = tmp->suiv_col;
	    }
	    tmp->suiv_col = p_cell;
	}
	else
	{
	    while (tmp->suiv_lig != NULL)
	    {
		tmp = tmp->suiv_lig;
	    }
	    tmp->suiv_lig = p_cell;
	}
}

void creuse_vers_pleine(int pleine[H][L], creuse_t* creuse) 
{
    cell_t* tmp;
    for (unsigned l = 0; l < H; l++)
    {
      tmp = creuse->lignes[l]; 
      for (unsigned c = 0; c < L; c++) 
      {
	  if (tmp == NULL || tmp->lig !=l || tmp->col !=c) 
	  {
	      pleine[l][c] = 0;	      
	  }
	  else
	  {
	      pleine[l][c] = tmp->val;
	      tmp = tmp->suiv_col;	      
	  }
	  
      }
    }
}

void pleine_vers_creuse(int pleine[H][L], creuse_t* creuse)
{
    for (unsigned l = 0; l < H; l++) 
    {   
	for (unsigned c = 0; c < L; c++) 
	{

            if (pleine[l][c] != 0)
	    {
		cell_t* p_cell = malloc(sizeof(cell_t));
		p_cell->val = pleine[l][c];
		p_cell->suiv_col = NULL;
		p_cell->suiv_lig = NULL;
		p_cell->lig = l;
		p_cell->col = c;
		if (creuse->colonnes[c] == NULL)
		{
		    creuse->colonnes[c] = p_cell;
		}
		else
		{
		    ajouteenqueue(creuse->colonnes[c],p_cell,0);   
		}
		if (creuse->lignes[l] == NULL)
		{
		    creuse->lignes[l] = p_cell;
		}
		else
		{
		    ajouteenqueue(creuse->lignes[l],p_cell,1);   
		}
	    }
        }
    }
}


int main(void)
{
    int pleine[H][L];
    init_pleine(pleine);
    affiche_pleine(pleine);
    creuse_t* creuse = init_creuse();
    pleine_vers_creuse(pleine, creuse);
    affiche_creuse(creuse);
    creuse_vers_pleine(pleine,creuse);
    affiche_pleine(pleine);
    liberer_creuse(creuse);
    //zero

    init_pleine_constante(pleine,0);
    affiche_pleine(pleine);
    creuse = init_creuse();
    pleine_vers_creuse(pleine, creuse);
    affiche_creuse(creuse);
    creuse_vers_pleine(pleine,creuse);
    affiche_pleine(pleine);
    liberer_creuse(creuse);
//pleine
    init_pleine_constante(pleine,1);
    affiche_pleine(pleine);
    creuse = init_creuse();
    pleine_vers_creuse(pleine, creuse);
    affiche_creuse(creuse);
    creuse_vers_pleine(pleine,creuse);
    affiche_pleine(pleine);
    liberer_creuse(creuse);

    return 0;
}

