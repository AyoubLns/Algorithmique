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
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

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

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
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
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}

/*************************************************/
/*                                               */
/*       PointeurSuite                           */
/*                                               */
/*************************************************/

Liste *PointeurSuite(Liste *l) {
    if (l != NULL) {
        return &((*l)->suivant);
    } else { // Gestion du cas où la liste est vide
        return NULL;
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

/*************************************************/
/*                                               */
/*        UnPlusDeuxEgalTrois                    */
/*                                               */
/*************************************************/

bool UnPlusDeuxEgalTrois(Liste l){
    if ( estVide(l) ){  //Si liste vide , alors renvoi vrai
        return TRUE;
    } else if ( estVide(suite(l)) ){ // Si liste contient que 0, alors vrai, sinon faux
        return premier(l) == 0;
    } else if ( estVide(suite(suite(l))) ) { // Si liste contient 2 élément x, y et que x+y = 0, alors vrai, sinon faux
        return premier(l) + premier(suite(l)) == 0;   
    }else {  
        return premier(l) + premier(suite(l)) == premier(suite(suite(l)));            
    }
    return FALSE;
}


void testUnPlusDeuxEgalTrois(){
    printf("Test UnPlusDeuxEgalTrois\n");
    Liste l;
    initVide (&l) ;
    printf("Liste vide : %b\n",UnPlusDeuxEgalTrois(l));
    
    empile(0, &l) ;
    printf("Liste à un seul élément [0] : %b\n", UnPlusDeuxEgalTrois(l));
    depile(&l);
    empile(8, &l);
    printf("Liste à un seul élément [8] : %b\n", UnPlusDeuxEgalTrois(l));
    
    
    empile(-8, &l);
    printf("Liste à deux éléments [-8, 8] : %b\n", UnPlusDeuxEgalTrois(l));
    depile(&l);
    empile(5, &l) ;
    printf("Liste à deux éléments [5, 8] : %b\n", UnPlusDeuxEgalTrois(l));
    
    empile(3, &l) ;
    printf("Liste valide : %b\n", UnPlusDeuxEgalTrois(l));
    depile(&l);
    empile(7, &l);
    printf("Liste invalide : %b\n", UnPlusDeuxEgalTrois(l));
    
}


/*************************************************/
/*                                               */
/*          Croissante                           */
/*                                               */
/*************************************************/

bool Croissante(Liste l){
    // La liste vide est forcément croissante
    if (estVide(l))
        return TRUE;
    
    // Sinon
    while(!estVide(suite(l))){
        if (premier(l) > premier(suite(l))) 
            return FALSE;  // Si un élément est plus grand que son suivant, alors la liste n'est pas croissante
        l = suite(l);
    }
    return TRUE;

}

void testCroissante(){
    Liste l;
    initVide(&l);
    
    printf("\nTest Croissante\n");
    
    printf("Liste vide : %b\n", Croissante(l));
    
    empile(10, &l);
    printf("Liste à 1 élément : %b\n", Croissante(l));
    
    empile(9, &l);
    empile(8, &l);
    empile(7, &l);
    empile(6, &l);
    empile(5, &l);
    empile(4, &l);
    empile(3, &l);
    empile(2, &l);
    empile(1, &l);
    printf("Liste valide [1-9]: %b\n", Croissante(l));
    
    empile(15, &l);
    printf("Liste invalide [15, 1-9]: %b\n", Croissante(l));
       
}


/*************************************************/
/*                                               */
/*          NombreMemePosition                   */
/*                                               */
/*************************************************/

int NombreMemePositionRec(Liste l1, Liste l2){
    // Si l'une des listes est vide, il n'y a pas d'éléments aux mêmes positions
    if(estVide(l1) || estVide(l2)){ 
        return 0; 
    }
    else {
        // Comparaison des éléments aux positions actuelles dans les deux listes
        if ( premier(l1) == premier(l2) ) { 
            // Si les éléments sont égaux, on ajoute 1 et continue avec les éléments suivants
            return 1 + NombreMemePositionRec(suite(l1), suite(l2)); 
        } else { 
            // Si les éléments ne sont pas égaux, on passe aux éléments suivants sans ajouter 1
            return NombreMemePositionRec(suite(l1), suite(l2)); }
    }
}

int NombreMemePositionIter(Liste l1, Liste l2){
    int cpt = 0;
    
    while (!estVide(l1) || !estVide(l1)) {
        // Comparaison des éléments aux positions actuelles dans les deux listes
        if ( premier(l1) == premier(l2) ) { 
            // Si les éléments sont égaux, on incrémente le compteur
            cpt++; 
        }
        l1 = suite(l1);
        l2 = suite(l2);
    }
    return cpt;
}

int NBRaux(Liste l1, Liste l2, int acc){
    if(estVide(l1) || estVide(l2)){ 
        return acc; 
    }
    else {
        if ( premier(l1) == premier(l2) ) { 
            NBRaux( suite(l1), suite(l2), acc+1); 
        } else { 
            NBRaux( suite(l1), suite(l2), acc); }
    }
}

int NombreMemePositionRecFonc(Liste l1, Liste l2){
    return NBRaux(l1, l2, 0);
}

void NBRaux2(Liste l1, Liste l2, int *acc){
    if (!estVide(l1) && !estVide(l2)) {
        if ( premier(l1) == premier(l2) ) {
            *acc = *acc + 1;
        }
        NBRaux2(suite(l1), suite(l2), acc);
    }
}

int NombreMemePositionRecProc(Liste l1, Liste l2){
    int cpt = 0;
    NBRaux2(l1, l2, &cpt);
    return cpt;
}

void testNombreMemePosition(){
    Liste l1;
    Liste l2;
    initVide(&l1);
    initVide(&l2);
    
    printf("\nTest NombreMemePosition\n");
    
    printf("2 Liste vide : %d\n", NombreMemePositionRecFonc(l1, l2));
    
    empile(1, &l1);
    printf("1 Liste vide et l'autre non : %d\n", NombreMemePositionRecFonc(l1, l2));
    
    empile(1, &l2);
    empile(2, &l1);
    empile(2, &l2);
    printf("Liste de taille 2 avec exactement les mêmes éléments aux mêmes indices : %d\n", NombreMemePositionRecFonc(l1, l2));
    
    empile(3, &l2);
    empile(8, &l1);
    printf("Meme Liste avec 2 nouveaux éléments différents : %d\n", NombreMemePositionIter(l1, l2));
    
}


/*************************************************/
/*                                               */
/*          FonctVireDernier                     */
/*                                               */
/*************************************************/
Liste FonctVireDernierRec(Liste l) {
    // Si la liste est vide ou à un élément, renvoyer la liste vide (NULL)
    if (estVide(l) || estVide(suite(l))) {
        return NULL;
    // On s'arrête à l'avant dernière élément
    } else if (estVide(suite(suite(l)))) { 
        return ajoute(premier(l), NULL);
    // Renvoyer une nouvelle liste avec le premier élément et la liste sans le dernier élément
    } else {
        return ajoute(premier(l), FonctVireDernierRec(suite(l)));
    }
}

Liste FonctVireDernierIter(Liste l) {
    // Si la liste ou a un element est vide, renvoyer la liste vide (NULL)
    if (estVide(l) || estVide(suite(l))) { 
        return NULL;
    }
    // Initialisation d'une nouvelle liste vide
    Liste res;
    initVide(&res);
    
    //Liste permet de nous obtenir l'élément suivant de la Liste res
    Liste *tmp = &res;
    // Boucle itérative pour empiler les éléments jusqu'au dernier élément de la liste
    while ( !estVide(suite(l)) ){ 
        empile(premier(l), tmp);
        tmp = PointeurSuite(tmp);
        l = suite(l);
    }
    return res;
}

void testFonctVireDernierRec(){
    printf("\nTest FonctVireDernier\n");
    Liste l;
    initVide(&l);
    printf("Test Liste Vide (bool): %b\n", estVide(FonctVireDernierRec(l)));
    
    empile(5, &l);
    empile(4, &l);
    empile(3, &l);
    empile(2, &l);
    empile(1, &l);
    printf("Liste avant appel à FonctVireDernierRec : ");
    affiche_rec(l);

    Liste l2 = FonctVireDernierRec(l);
    printf("Liste après à FonctVireDernierRec : ");
    affiche_rec(l2);

    l2 = FonctVireDernierIter(l2);
    printf("Liste après à FonctVireDernierIter : ");
    affiche_rec(l2);
    
    l2 = FonctVireDernierRec(l2);
    printf("Liste après à FonctVireDernierRec : ");
    affiche_rec(l2);
    
    l2 = FonctVireDernierIter(l2);
    printf("Liste après à FonctVireDernierIter : ");
    affiche_rec(l2);    
}


/*************************************************/
/*                                               */
/*           AjouteDevantPremierZero             */
/*                                               */
/*************************************************/

void AjouteDevantPremierZero(Liste *l, int x){
    if (!estVide(*l)){
        // Vérifie si le premier élément de la liste est zéro
        if (premier(*l) == 0){
            // Si le premier élément est zéro, ajoute l'élément 'x' devant le premier zéro
            *l = ajoute(x, *l);
        } else {
            // Si le premier élément n'est pas zéro, continue la recherche dans la suite de la liste
            AjouteDevantPremierZero(PointeurSuite(l), x);
        }
    }
}

void testAjouteDevantPremierZero(){
    Liste l;
    initVide(&l);
    printf("\nTest AjouteDevantPremierZero\n");
    
    empile(1, &l);
    empile(0, &l);
    AjouteDevantPremierZero(&l, 8);
    printf("Liste qui commence par 0 : ");
    affiche_rec(l);
    
    VideListe(&l);
    
    empile(3, &l);
    empile(2, &l);
    empile(0, &l);
    empile(1, &l);
    printf("Avant appel à la fonction : ");
    affiche_rec(l);
    AjouteDevantPremierZero(&l, 8);
    printf("Après appel à la fonction : ");
    affiche_rec(l);
}

/*************************************************/
/*                                               */
/*           AjouteDevantDenierZero              */
/*                                               */
/*************************************************/

void AjouteDevantDernierZeroIter(Liste *l, int x){
    Liste *tmp;
    initVide(tmp);
    while(!estVide(*l)){
        if(premier(*l) == 0){
            tmp = l;
        }
        l = PointeurSuite(l);
    }
    if(tmp != NULL){
        *tmp = ajoute(x, *tmp);
    }else{
        *l = ajoute(x, *l);
    }  
}

void ADDZRT_Aux(Liste *l, int x, Liste *p){
    if ((*l)->suivant == NULL){
        if (p==NULL){
            empile(x, l);
        } else{
            empile(x, p);
        }
        
    } else {
        if (premier(*l) == 0){
            p=l;
        }
        ADDZRT_Aux(&((**l).suivant), x, p);
   }
}

void AjouteDevantDernierZeroRecTerminal(Liste *l, int x){
    if (*l == NULL){
        empile(x, l);
    } else {
        Liste *p = NULL;
        ADDZRT_Aux(l, x, p);
    }
}


void ADDZRO_Aux(Liste *l, int x, bool *vu){
    if (*l == NULL){
        if (NOT *vu){
            *l = ajoute(x, *l);
        }
    } else {
        if (premier(*l) == 0){
            *vu = TRUE;
        }
        ADDZRO_Aux(PointeurSuite(l), x, vu);
        if ((premier(*l) == 0) && *vu){
            *l = ajoute(x, *l);
            *vu = FALSE;
        }
    }

}


void AjouteDevantDernierZeroRecOut(Liste *l, int x){
    bool *vu = FALSE;
    ADDZRO_Aux(l, x, vu);
}


void testAjouteDevantDernierZero(){
    Liste l;
    initVide(&l);
    printf("\nTest AjouteDevantDernierZero\n");
    
    empile(1, &l);
    empile(0, &l);
    AjouteDevantDernierZeroRecTerminal(&l, 8);
    printf("Liste qui commence par 0 : ");
    affiche_rec(l);
    
    VideListe(&l);
    
    empile(3, &l);
    empile(0, &l);
    empile(2, &l);
    empile(0, &l);
    empile(1, &l);
    printf("Avant appel à la fonction : ");
    affiche_rec(l);
    AjouteDevantDernierZeroIter(&l, 8);
    printf("Après appel à la fonction : ");
    affiche_rec(l);
    
    VideListe(&l);
    
    empile(1, &l);
    printf("Liste sans 0 :\nAvant appel à la fonction : ");
    affiche_rec(l);
    AjouteDevantDernierZeroRecTerminal(&l, 8);
    printf("Après appel à la fonction : ");
    affiche_rec(l);
    
    VideListe(&l);
    printf("Liste Vide :\nAprès appel à la fonction : ");
    AjouteDevantDernierZeroIter(&l, 8);
    affiche_rec(l);
    
}

/*************************************************/
/*                                               */
/*           Tic                                 */
/*                                               */
/*************************************************/

void Tic(Liste *l){
    while(!estVide(*l)){
        if(premier(*l) != 0){
            empile(0, l);
            l = PointeurSuite(PointeurSuite(l));
        } else {
            depile(l);
            if(estVide(*l) || premier(*l) != 0){
                return;
            } 
        }
    }
}


void testTic(){
    Liste l;
    initVide(&l);
    printf("\nTest Tic\n");
    
    printf("Liste vide avant appel à la fonction : ");
    affiche_rec(l);
    Tic(&l);
    printf("Liste vide après appel à la fonction : ");
    affiche_rec(l);
    
    empile(0, &l);
    
    printf("Liste [0] avant appel à la fonction : ");
    affiche_rec(l);
    Tic(&l);
    printf("Liste [0] après appel à la fonction : ");
    affiche_rec(l);
    
    empile(2, &l);
    empile(1, &l);
    empile(3, &l);
    printf("Liste (sans 0) avant appel à la fonction : ");
    affiche_rec(l);
    Tic(&l);
    printf("Liste (sans 0) après appel à la fonction : ");
    affiche_rec(l);
    VideListe(&l);
    
    empile(3, &l);
    empile(2, &l);
    empile(0, &l);
    empile(1, &l);
    printf("Liste (avec un seul 0) avant appel à la fonction : ");
    affiche_rec(l);
    Tic(&l);
    printf("Liste (avec un seul 0) après appel à la fonction : ");
    affiche_rec(l);
    
    empile(3, &l);
    empile(2, &l);
    empile(0, &l);
    empile(0, &l);
    empile(0, &l);
    empile(1, &l);
    printf("Liste (avec succession de 0) avant appel à la fonction : ");
    affiche_rec(l);
    Tic(&l);
    printf("Liste (avec succession de 0) après appel à la fonction : ");
    affiche_rec(l);
    
    VideListe(&l);
    
    empile(0, &l);
    empile(0, &l);
    empile(0, &l);
    empile(1, &l);
    printf("Liste (avec succession de 0 en fin) avant appel à la fonction : ");
    affiche_rec(l);
    Tic(&l);
    printf("Liste (avec succession de 0 en fin) après appel à la fonction : ");
    affiche_rec(l);
}
                
/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

int main(int argc, char** argv)
{
    Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    VideListe(&l);
    
    testUnPlusDeuxEgalTrois();
    testCroissante();
    testNombreMemePosition();
    testFonctVireDernierRec();
    testAjouteDevantPremierZero();
    testAjouteDevantDernierZero();
    testTic();
    
    return 0;
}