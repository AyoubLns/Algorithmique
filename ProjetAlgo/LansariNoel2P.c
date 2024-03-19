
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

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*          definition type liste de liste       */
/*                                               */
/*************************************************/

typedef struct BlocListe
{
    Liste liste;
    struct BlocListe *suivant;
} BlocListe;

typedef BlocListe *ListeDeListes;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

void initVideListe(ListeDeListes *listeL);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

bool estVideListe(ListeDeListes listeL);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

Liste premierListe(ListeDeListes listeL);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

ListeDeListes ajouteListe(Liste l, ListeDeListes listeL);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

void empileListe(Liste l, ListeDeListes* listeL);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

ListeDeListes suiteListe(ListeDeListes listeL);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

void depileListe(ListeDeListes* listeL);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

void affiche_recListe(ListeDeListes l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

void initVideListe(ListeDeListes *listeL){
    *listeL = NULL;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

bool estVideListe(ListeDeListes listeL)
{
    return listeL == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste premierListe(ListeDeListes listeL)
{
    return listeL->liste;
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

ListeDeListes ajouteListe(Liste l, ListeDeListes listeL)
{
    ListeDeListes tmp = (ListeDeListes) malloc(sizeof(BlocListe)) ;
    tmp->liste = l ;
    tmp->suivant = listeL ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

void empileListe(Liste l, ListeDeListes *listeL)
{
      *listeL = ajouteListe(l,*listeL) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}

ListeDeListes suiteListe(ListeDeListes listeL)
{
    return listeL->suivant ;
}

void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

void depileListe(ListeDeListes *listeL)
{
    ListeDeListes tmp = *listeL ;
    *listeL = suiteListe(*listeL) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("-\n");
    else
    {
       if(estVide(suite(l))){
            printf("%d", premier(l));
            affiche_rec(suite(l));
       }else{
            printf("%d, ", premier(l));
            affiche_rec(suite(l));
       }
    }
}

void affiche_recListe(ListeDeListes listeL){
    if(estVideListe(listeL))
        printf("\n");
    else
    {
        affiche_rec( premierListe(listeL) );
        affiche_recListe(suiteListe(listeL));
    }
}

/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

void VideListeDeListes(ListeDeListes *listeL)
{
    if(NOT(estVideListe(*listeL)))
    {
        depileListe(listeL);
        VideListeDeListes(listeL);
    }
      
}

/*************************************************/
/*                                               */
/*           Predeclarations                     */
/*           Permutation                         */
/*                                               */
/*************************************************/

ListeDeListes Permutations(int n);

ListeDeListes Concat(ListeDeListes L1, ListeDeListes L2);

ListeDeListes ATLTP(int x, ListeDeListes listeL);

ListeDeListes ATP(int x, Liste L);

ListeDeListes AETTL(int x, ListeDeListes listeL);

/*************************************************/
/*                                               */
/*           Permutation                         */
/*                                               */
/*************************************************/

ListeDeListes Permutations(int n) {
    if(n == 0){
        return ajouteListe(NULL, NULL);
    }else{
        return ATLTP(n, Permutations(n-1));
    }
}

void testPermutations(){
    printf("\n --Test Permutations-- \n");
    
    int n = 3;
    printf("Permutation %d : \n", n);
    printf("[ \n");
    affiche_recListe(Permutations(3));
    printf("] \n");
    
}

ListeDeListes Concat(ListeDeListes L1, ListeDeListes L2){
    if(estVideListe(L1)){
        return L2;
    }else{
        return ajouteListe(premierListe(L1), Concat(suiteListe(L1), L2));
    }
}

void testConcat(){
    printf("\n --Test Concat-- \n");
    
    ListeDeListes listeL1;
    initVideListe(&listeL1);
    Liste l1;
    initVide(&l1);
    empile(3, &l1);
    empile(1, &l1);
    empile(2, &l1);
    empileListe(l1, &listeL1);
    
    ListeDeListes listeL2;
    initVideListe(&listeL2);
    
    Liste l2;
    initVide(&l2);
    empile(5, &l2);
    empile(4, &l2);
    empile(0, &l2);
    empileListe(l2, &listeL2);
    
    printf("Liste1 : ");
    printf("[ \n");
    affiche_recListe(listeL1);
    printf("] \n");
    
    printf("Liste2 : ");
    printf("[ \n");
    affiche_recListe(listeL2);
    printf("] \n");
    
    printf("Concat(Liste1, Liste2) : ");
    printf("[ \n");
    affiche_recListe(Concat(listeL1, listeL2));
    printf("] \n");
    VideListe(&l1);
    VideListe(&l2);
    
    VideListeDeListes(&listeL1);
    VideListeDeListes(&listeL2);
}

ListeDeListes ATLTP(int x, ListeDeListes listeL){
    if(estVideListe(listeL)){
        ListeDeListes res;
        initVideListe(&res);        
        return res;
    }else{
        return Concat(ATP(x, premierListe(listeL)), ATLTP(x, suiteListe(listeL)));
    }
}

void testATLTP(){
    printf("\n --Test ATLTP-- \n");
    
    ListeDeListes listeL1;
    initVideListe(&listeL1);
    
    Liste l1;
    initVide(&l1);
    empile(9, &l1);
    empile(7, &l1);
    empile(5, &l1);
    empileListe(l1, &listeL1);
    
    Liste l2;
    initVide(&l2);
    empile(2, &l2);
    empileListe(l2, &listeL1);
    
    Liste l3;
    initVide(&l3);
    empile(8, &l3);
    empile(3, &l3);
    empileListe(l3, &listeL1);
    
    Liste l4;
    initVide(&l4);
    empileListe(l4, &listeL1);
    
    printf("Liste : ");
    printf("[ \n");
    affiche_recListe(listeL1);
    printf("] \n");
    int n = 4;
    printf("ATLTP(%d, Liste) : \n", n);
    printf("[ \n");
    affiche_recListe(ATLTP(n, listeL1));
    printf("] \n");
    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
    VideListe(&l4);
    
    VideListeDeListes(&listeL1);
}

ListeDeListes ATP(int x, Liste l){
    if(estVide(l)){
        return ajouteListe(ajoute(x, l), NULL);
    }else{
        return ajouteListe(ajoute(x, l), AETTL(premier(l), ATP(x, suite(l))));
    }
}

void testATP(){
    printf("\n --Test ATP-- \n");
    
    Liste l1;
    initVide(&l1);
    empile(9, &l1);
    empile(7, &l1);
    empile(5, &l1);
    
    printf("Liste : ");
    printf("[ \n");
    affiche_rec(l1);
    printf("] \n");
    int n = 4;
    printf("ATP(%d, Liste) : \n", n);
    printf("[ \n");
    affiche_recListe(ATP(n, l1));
    printf("] \n");
    VideListe(&l1);

}

ListeDeListes AETTL(int x, ListeDeListes listeL){
    if(estVideListe(listeL)){
        ListeDeListes res;
        initVideListe(&res);        
        return res;
    }else{
        return ajouteListe(ajoute(x, premierListe(listeL)), AETTL(x, suiteListe(listeL)));
    }
}

void testAETTL(){
    printf("\n --Test AETTL-- \n");
    
    ListeDeListes listeL1;
    initVideListe(&listeL1);
    
    Liste l1;
    initVide(&l1);
    empile(9, &l1);
    empile(7, &l1);
    empile(3, &l1);
    empileListe(l1, &listeL1);
    
    Liste l2;
    initVide(&l2);
    empile(2, &l2);
    empileListe(l2, &listeL1);
    
    Liste l3;
    initVide(&l3);
    empile(8, &l3);
    empile(4, &l3);
    empileListe(l3, &listeL1);
    
    Liste l4;
    initVide(&l4);
    empileListe(l4, &listeL1);
    
    printf("Liste : ");
    printf("[ \n");
    affiche_recListe(listeL1);
    printf("] \n");
    int n = 6;
    printf("AETTL(%d, Liste) : \n", n);
    printf("[ \n");
    affiche_recListe(AETTL(n, listeL1));
    printf("] \n");
    VideListe(&l1);
    VideListe(&l2);
    VideListe(&l3);
    VideListe(&l4);
    
    VideListeDeListes(&listeL1);
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

int main(int argc, char** argv)
{
    testPermutations();
    testConcat();
    testATLTP();
    testATP();
    testAETTL();
    return 0;
}




