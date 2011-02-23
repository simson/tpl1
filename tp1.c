/**
 * @file   tp1.c
 * @author Siméon Marijon <simson@laptop-de-sim>
 * @date   Mon Feb  7 12:20:31 2011
 * 
 * @brief  TP en temps libre n°1
 * 
 * 
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define L 7  /**< Longueur de la patrice pleine */
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


void mult_pleine(int pleine[H][L], int fac)
{
    for (unsigned l = 0; l < H; l++) {                        // parcours sur les lignes
        for (unsigned c = 0; c < L; c++) {                    // parcours sur les colones
           pleine[l][c] = pleine[l][c] * fac ;   // on affiche chaque case de la matrice pleine
        }
    }
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
typedef struct{
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
    assert(creuse != NULL);                      //Vérification du malloc
    creuse->nbr_lig = H;                         // initialisation des nombres
    creuse->nbr_col = L;                         // de lignes et de colonnes
    creuse->lignes = calloc(creuse->nbr_lig, sizeof(cell_t*)); //allocation des tableau de listes
    assert(creuse->lignes != NULL);              // Vérification du malloc
    creuse->colonnes = calloc(creuse->nbr_col, sizeof(cell_t*)); 
    assert(creuse->colonnes != NULL);            // Vérification du malloc
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
    cell_t* tmp;                               // Déclaration d'un pointeur temporaire sur une cellule, en fait une liste
    for (unsigned l = 0; l < H; l++)           // On parcours le tableau des listes de lignes
    {
	tmp = creuse->lignes[l];               // Tmp devient la liste lignes[l]  
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
 * Multiplication de matrice creuse 
 * @param creuse la matrice à multiplié
 * @param fac le facteur
 */
void mult_creuse(creuse_t* creuse, int fac) 
{
    cell_t* tmp;                               // Déclaration d'une liste temporaire
    for (unsigned l = 0; l < H; l++)           // On parcours le tableau des listes de lignes
    {
      tmp = creuse->lignes[l]; 
      
      for (unsigned c = 0; c < L; c++)         // On parcours les colones
      {                                        // le vrai parcours se fait sur la liste tmp
	  if (! (tmp == NULL || tmp->lig !=l || tmp->col !=c)) 
	  {                                    // Si on a atteint la fin de la liste ou
	                                       // si la cellule en tête de liste ne correspond pas à l'indice courant
	      tmp->val = tmp->val * fac;       // On multiplie la valeur de la cellulle
	      tmp = tmp->suiv_col;             // On avance dans la liste
	  }
      }
    }
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
	    while (tmp->suiv_col != NULL)     // On parcours  la liste des colonnes jusqu'au dernier element
	    {
		tmp = tmp->suiv_col;
	    }
	    tmp->suiv_col = p_cell;           // On ajoute en fin 
	}
	else
	{
	    while (tmp->suiv_lig != NULL)     // On parcours la liste des lignes jusqu'au dernier element
	    {
		tmp = tmp->suiv_lig;
	    }
	    tmp->suiv_lig = p_cell;          // On ajoute en fin de la liste
	}
}
/** 
 * @brief Transforme une matrice creuse en matrice pleine
 * @param pleine Matrice pleine à creer
 * @param creuse pointeur sur la matrice à transformer
 */
void creuse_vers_pleine(int pleine[H][L], creuse_t* creuse) 
{
    cell_t* tmp;                                            // Déclaration d'une liste temporaire
    for (unsigned l = 0; l < H; l++)                        // On parcours le tableau ligne 
    {
	tmp = creuse->lignes[l];                            // Allocation de la liste temporaire
      for (unsigned c = 0; c < L; c++) 
      {
	  if (tmp == NULL || tmp->lig !=l || tmp->col !=c) 
	  {                                                // Si on a atteint la fin de la liste ou si
                                                           // la cellule pointé ne correspond pas à l'indice courant
	      pleine[l][c] = 0;	                           // On insert 0 dans la matrice pleine à l'indice courant
	  }
	  else                                             // Sinon
	  {
	      pleine[l][c] = tmp->val;                     // On stocke la valeur de la cellulle dans la matrice pleine
	                                                   // à l'indice courant
	      tmp = tmp->suiv_col;	                   // et on avance dans la liste
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
	for (unsigned c = 0; c < L; c++) // On parcours toute la matrice pleine
	{

            if (pleine[l][c] != 0)       // Si la valeur de la case est différente de 0
	    {
		cell_t* p_cell = malloc(sizeof(cell_t)); // allocation d'une nouvelle cellule 
		assert(p_cell != NULL);                  //Vérification du malloc
		p_cell->val = pleine[l][c];              // Stockage de la valeur dans la celulle
		p_cell->suiv_col = NULL;                 // Cette cellulle sera (temporairement) en fin des deux listes
		p_cell->suiv_lig = NULL;                 // auxquelles elle appartient
		p_cell->lig = l;                         // Stockage de la position réelle de la cellule
		p_cell->col = c;
		if (creuse->colonnes[c] == NULL)         // Vérification que la liste colonnes[c] n'est pas vide
		{
		    creuse->colonnes[c] = p_cell;        // Si oui on la place en tête
		}
		else
		{
		    ajouteenqueue(creuse->colonnes[c],p_cell,0); //sinon en queue   
		}
		if (creuse->lignes[l] == NULL)          //Idem pour la liste ligne[l]
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
    int pleine[H][L];                        // Déclaration de la matrice pleine
    int pleine2[H][L];                       // Déclaration d'une deuxième matrice pleine
    init_pleine(pleine);                     // remplissage de la matrice pleine
    printf("Matrice pleine \n\n");
    affiche_pleine(pleine);                  // affichage de la matrice pleine
    creuse_t* creuse = init_creuse();        // Déclaration, allocation et initialisation de la matrice creuse
    pleine_vers_creuse(pleine, creuse);      // Conversion de la matrice pleine en creuse
    printf("Conversion de la matrice pleine en creuse \n\n");
    affiche_creuse(creuse);                  // Affichage de la matrice creuse
    creuse_vers_pleine(pleine2,creuse);      // Reconversion de la matrice dans une autre pleine 
    printf("Conversion de la matrice creuse en pleine \n\n");
    affiche_pleine(pleine2);                 // Affichage de la matrice pleine généré par la conversion (pour validation)
    mult_creuse(creuse, 4);                  // Multiplication de la matrice creuse par 4
    printf("Multiplication de la matrice creuse par 4 \n\n");
    affiche_creuse(creuse);                  // affichage de la matrice creuse multiplié
    creuse_vers_pleine(pleine,creuse);       // Conversion de la matrice
    printf("Conversion de la matrice pleine en creuse multiplié \n\n");
    affiche_pleine(pleine);                  // Affichage du résultat
    printf("Multiplication de la matrice pleine par 4 \n\n");
    mult_pleine(pleine2, 4);                  // Multiplication de la matrice pleine par 4
    affiche_pleine(pleine2);                 // Affichage de la matrice pleine multiplié (pour validation)
    liberer_creuse(creuse);                  // Libération de la matrice creuse 
//zero
    printf("\n\n Nouvelle Matrice \n\n");
    // Test avec la matrice nulle
    init_pleine_constante(pleine,0);
    printf("Matrice pleine \n\n");         
    affiche_pleine(pleine);                  // Affichage de la matrice pleine 
    creuse = init_creuse();                  // Initialisation de la matrice creuse
    pleine_vers_creuse(pleine, creuse);      // Conversion vers creuse
    printf("Conversion de la matrice pleine en creuse \n\n");
    affiche_creuse(creuse);                  // Affichage du résultat
    mult_creuse(creuse, 4);                  // Multiplication de la matrice creuse
    printf("Multiplication de la matrice creuse par 4 \n\n");
    affiche_creuse(creuse);                  // Affichage du résultat
    mult_pleine(pleine,4);                     // Multiplication de la matrice pleine
    printf("Multiplication de la matrice pleine par 4 \n\n");
    affiche_pleine(pleine);                  // Affichage du résultat
    printf("Conversion de la matrice pleine en creuse\n\n");
    creuse_vers_pleine(pleine2,creuse);
    affiche_pleine(pleine);                  // Affichage de la conversion de la matrice pleine pour validation
    liberer_creuse(creuse);                  // Libération de la matrice creuse
//pleine
    printf("\n\n Nouvelle Matrice \n\n");
    // Test avec la matrice pleine de 1
    init_pleine_constante(pleine,1);
    printf("Matrice pleine \n\n");         
    affiche_pleine(pleine);                  // Affichage de la matrice pleine 
    creuse = init_creuse();                  // Initialisation de la matrice creuse
    pleine_vers_creuse(pleine, creuse);      // Conversion vers creuse
    printf("Conversion de la matrice pleine en creuse \n\n");
    affiche_creuse(creuse);                  // Affichage du résultat
    mult_creuse(creuse, 6);                  // Multiplication de la matrice creuse
    printf("Multiplication de la matrice creuse par 6 \n\n");
    affiche_creuse(creuse);                  // Affichage du résultat
    mult_pleine(pleine,6);                     // Multiplication de la matrice pleine
    printf("Multiplication de la matrice pleine par 6 \n\n");
    affiche_pleine(pleine);                  // Affichage du résultat
    printf("Conversion de la matrice pleine en creuse \n\n");
    creuse_vers_pleine(pleine2,creuse);
    affiche_pleine(pleine);                  // Affichage de la conversion de la matrice pleine pour validation
    liberer_creuse(creuse);                  // Libération de la matrice creuse 
   return 0;
}

