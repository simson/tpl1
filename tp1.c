#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Fonctions de manipulation de matrices pleines

// definition de constantes globales
/**
 * @def L Largeur de la matrice pleine
 */
#define L 7			/**< Longueur de la patrice pleine */
#define H 4  /**<  Hauteur de la matrice pleine */





/** 
 * @brief initialise une matrice pleine avec des entiers aleatoires
 * @param pleine Matrice pleine à initialiser 
 */
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

/** 
 * @brief Initialisation d'une matrice pleine avec des constantes
 * @param pleine Matrice pleine à remplir
 * @param constante Constante à affecter à toutes les cases de la matrice
 */
void init_pleine_constante(int pleine[H][L], int constante)
{
    for (unsigned l = 0; l < H; l++) {
        for (unsigned c = 0; c < L; c++) {
	    pleine[l][c] = constante ; //remplissage de chaque case de la matrice avec la constante
        }
    }
}
// affiche une matrice pleine
/** 
 * @brief affiche la matrice pleine
 * @param pleine la matrice pleine à afficher
 */
void affiche_pleine(int pleine[H][L])
{
    for (unsigned l = 0; l < H; l++) {                        // parcours sur les lignes
        for (unsigned c = 0; c < L; c++) {                    // parcours sur les colones
            printf("%5d ", pleine[l][c]);   // on affiche chaque case de la matrice pleine
        }
        printf("\n");                      
    }
    printf("\n");
}



/**
 * @struct cell_t
 * @brief le type cellule
 */
typedef struct cell_t {
    int val;			                     /**< valeur de la cellule */
    unsigned lig, col;            /**< position de la cellule dans la matrice  */
    struct cell_t *suiv_lig, *suiv_col; /**<  liens vers les cellules voisines */
}cell_t;


/**
 * @struct creuse_t
 * @brief le type matrice creuse
 */
typedef struct creuse_t {
    unsigned nbr_lig;                   /**< le nombre de lignes de la matrice */
    struct cell_t **lignes;                            /**< tableau des lignes */
    unsigned nbr_col;                   /**< le nombre de lignes de la matrice */
    struct cell_t **colonnes;                        /**< tableau des colonnes */
}creuse_t;

/** 
 * @brief Initialise une matrice creuse (réservation des tableaux)
 * @return Un pointeur sur la matrice creuse (vide) nouvellement créée
 */
creuse_t* init_creuse()
{
    
    creuse_t* creuse = malloc(sizeof(creuse_t)); // allocation de la structure
    creuse->nbr_lig = H;                         // initialisation des nombres
    creuse->nbr_col = L;                         // de lignes et de colonnes
    creuse->lignes = calloc(creuse->nbr_lig, sizeof(cell_t*)); //allocation des tableau de listes
    creuse->colonnes = calloc(creuse->nbr_col, sizeof(cell_t*)); 
    return creuse;                               // retourne la matrice initialisé
}

/** 
 * @brief fonction de libération de liste
 * @param liste la liste à libérer
 */
void liberer_liste(cell_t* liste)
{
    cell_t* a_supprimer;                        // définition du pointeur à supprimer
    while(liste != NULL)                        // on parcours la liste
    {
	a_supprimer = liste;                    // la première valeur de la liste
	liste = liste->suiv_col;                // on avance dans la liste
	free(a_supprimer);                      // on supprime l'ancienne tête de la liste
    }
}
/** 
 * @brief Fonction de libération d'une matrice creuse
 * @param creuse Pointeur sur la matrice à libérer
 */
void liberer_creuse(creuse_t* creuse)
{
    for (unsigned l = 0; l < H; l++)            // On parcours le tableau de liste des lignes
    {
	liberer_liste(creuse->lignes[l]);       // On libère chacune des listes du tableau
    }
    free(creuse->lignes);                       // On libère le tableau de liste des lignes
    free(creuse->colonnes);                     // On libère le tableau de liste des colonnes
    free(creuse);                               // On libère la structure de la matrice creuse
}

/** 
 * @brief Affiche une matrice creuse
 * @param creuse Pointeur sur la matrice à afficher
 */
void affiche_creuse(creuse_t* creuse) 
{
    cell_t* tmp;                               // Allocation d'un pointeur temporaire
    for (unsigned l = 0; l < H; l++)           // On parcours le tableau des listes de lignes
    {
      tmp = creuse->lignes[l]; 
      for (unsigned c = 0; c < L; c++)         // On parcours les colones 
      {                                        // le vrai parcours se fait sur la liste tmp
	  if (tmp == NULL || tmp->lig !=l || tmp->col !=c) 
	  {                                    // Si on a atteint la fin de la liste ou
	                                       // si la cellule en tête de liste ne correspond pas à l'indice courant
	      printf("%5d ", 0);	       // On imprime 0
	  }
	  else
	  {
	      printf("%5d ", tmp->val);       // Sinon on imprime la valeur 
	      tmp = tmp->suiv_col;            // et on avance dans la liste
	  }
      }
      printf("\n");   
    }
    printf("\n");   
}

/** 
 * @brief Fonction d'ajout en queue dans une liste
 * @param liste_cell Pointeur sur la tête de liste ou l'on doit inserer la nouvelle cellule  
 * @param p_cell Pointeur sur la cellule à ajouter en fin de la fin
 * @param col Booléen permettant de selectionné le type de liste (ligne ou colonne)
 */
void ajouteenqueue(cell_t* liste_cell, cell_t* p_cell, short col)
{
    cell_t* tmp = liste_cell;                 // on créer une copie du pointeur sur la tête de la liste
    if (col)                                  // Disjonction des cas si on travaille sur une liste de colonnes ou de lignes
	{
	    while (tmp->suiv_col != NULL)     // On parcours la liste des colonnes
	    {
		tmp = tmp->suiv_col;
	    }
	    tmp->suiv_col = p_cell;           // On ajoute en fin 
	}
	else
	{
	    while (tmp->suiv_lig != NULL)     // On parcours la liste des colonnes
	    {
		tmp = tmp->suiv_lig;
	    }
	    tmp->suiv_lig = p_cell;          // On ajoute en fin
	}
}
/** 
 * @brief Transforme une matrice creuse en matrice pleine
 * @param pleine Matrice pleine à creer
 * @param creuse pointeur sur la matrice à transformer
 */
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
/** 
 * @param pleine la matrice pleine à transformer
 * @param creuse pointeur sur la futur matrice creuse à creer
 */
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

/** 
 * @brief Fonction principal 
 * @return valeur de sortie du programme
 */
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

