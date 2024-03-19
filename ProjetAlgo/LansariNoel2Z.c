
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct BlocZ {
    int valeur;
    struct BlocZ *next;
    struct BlocZ **prev;
    
} BlocZ;

typedef BlocZ ***ListeZ;

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initListeZ(ListeZ *acces){
    *acces = NULL;
}

void ZAjouteAvant(int x, ListeZ *acces){
    BlocZ *newBloc = (BlocZ *)malloc(sizeof(BlocZ));
    if (*acces == NULL){
        newBloc->valeur = x;
        newBloc->next = newBloc;
        newBloc->prev = &(newBloc->next);
        *acces = &(newBloc->prev);
        printf("Adresse premier élément : %d\n", &(newBloc));

    } else {
        newBloc->valeur = x;
        newBloc->next = ***acces;
        **acces = &(newBloc->next);
        
        ***acces = newBloc;
        
        newBloc->prev = **acces;
        
        *acces = &(newBloc->prev); 
    }
}

/*************************************************/
/*                                               */
/*                    Affiche                    */
/*                                               */
/*************************************************/

void afficheListeZ(ListeZ acces){
    BlocZ tmp = ***acces;
    printf("Premier élément de la Liste : %d\n", tmp.valeur);
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

int main(int argc, char** argv)
{
    
    return 0;
}




