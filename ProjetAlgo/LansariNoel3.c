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

typedef struct bloc_image
    { bool quatre ;
    struct bloc_image *hg, *hd, *bg, *bd ;
    } bloc_image ;

typedef bloc_image *Image ;

typedef struct Bloc
{
    char c;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

Image Blanc();

Image Noir();

Image Compose(Image i0, Image i1, Image i2, Image i3);

void Affichage(Image img);

void AffichageProfondeur(Image img);

void AP(Image img, int cpt);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

Image Blanc(){    
    Image res = (Image) malloc(sizeof(bloc_image));
    res -> quatre = FALSE;
    res -> hg = NULL;
    res -> hd = NULL;
    res -> bg = NULL;
    res -> bd = NULL;
    
    return res;
}

Image Noir(){
    return NULL;
}

Image Compose(Image i0, Image i1, Image i2, Image i3){
    Image res = (Image) malloc(sizeof(bloc_image));
    res -> quatre = TRUE;
    res -> hg = i0;
    res -> hd = i1;
    res -> bg = i2;
    res -> bd = i3;
    
    return res;
}


/*************************************************/
/*                                               */
/*          Affichage/AffichageProfondeur        */
/*                                               */
/*************************************************/

void Affichage(Image img){
    if(img == NULL) {
        printf("X");
    } else if (img -> quatre == FALSE){
        printf("o");
    } else {
        Affichage(img -> hg);
        Affichage(img -> hd);
        Affichage(img -> bg);
        Affichage(img -> bd);
        printf("*");
    }
}

void testAffichage() {
    Image img = Compose(Blanc(), Noir(), Blanc(), Noir());
    
    printf("\n~~~~ TEST AFFICHAGE ~~~~\n");
    printf("Affiche blanc : ");
    Affichage(Blanc());
    printf("\nAffiche noir : ");
    Affichage(Noir());
    printf("\nAffiche oXoX* : ");
    Affichage(img);
    printf("\n");
    
}

void AffichageProfondeur(Image img){
    int cpt = 0;
    AP(img, cpt);
}

void AP(Image img, int cpt){
    if(img == NULL) {
        printf("X%d ", cpt);
    } else if(img -> quatre == FALSE) {
        printf("o%d ", cpt);
    } else {
        AP(img -> hg, cpt+1);
        AP(img -> hd, cpt+1);
        AP(img -> bg, cpt+1);
        AP(img -> bd, cpt+1);
        printf("*%d ", cpt);
    }
}

void testAffichageProfondeur() {
    Image img = Compose(Blanc(), Noir(), Blanc(), Noir());
    
    printf("\n~~~~ TEST AFFICHAGE PROFONDEUR ~~~~\n");
    printf("Affiche blanc : ");
    AffichageProfondeur(Blanc());
    printf("\nAffiche noir : ");
    AffichageProfondeur(Noir());
    printf("\nAffiche oXoX* : ");
    AffichageProfondeur(img);
    printf("\n");
    
}

/*************************************************/
/*                                               */
/*                  Lecture                      */
/*                                               */
/*************************************************/

void initVide( Liste *L)
{
    *L = NULL ;
}

int premier(Liste l)
{
    return l->c ; 
}

Liste ajoute(char car, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->c = car;
    tmp->suivant = l ;
    return tmp ;
}

void empile(char c, Liste *L)
{
      *L = ajoute(c,*L) ; 
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


Image LectureBis(Liste *l){
    if(premier(*l) == 'X'){
        depile(l);
        return Noir();
    } else if(premier(*l) == 'o'){
        depile(l);
        return Blanc();
    } else if(premier(*l) == '*'){
        depile(l);
        Image bd = LectureBis(l);
        Image bg = LectureBis(l);
        Image hd = LectureBis(l);
        Image hg = LectureBis(l);
        return Compose(hg, hd, bg, bd);
    } else {
        depile(l);
        return LectureBis(l);
    }
}

Image Lecture() {
    Liste l;
    initVide(&l);
    char c;
    printf("Entrez une image avec les caractères X - o - * - ! (pour la fin) \n");
    while((c = getchar())!='!'){
        empile(c, &l);
    }
    return LectureBis(&l);
}

/*************************************************/
/*                                               */
/*            EstBlanche/EstNoire                */
/*                                               */
/*************************************************/


bool EstBlanche(Image img){
    if (img == NULL){ 
        return FALSE; 
    } else if (img->quatre == FALSE) { 
        return TRUE; 
    } else { 
        return EstBlanche(img -> hg) && EstBlanche(img -> hd) && EstBlanche(img -> bg) && EstBlanche(img -> bd);
    }
}

void testEstBlanche(){
    Image blanc = Blanc();
    Image noir = Noir();
    printf("\n~~~~ TEST EST BLANCHE ~~~~\n");
    printf("Image Blanche (o) : %b\n", EstBlanche(Blanc()));
    printf("Image Blanche (oooo*ooo*) : %b\n", EstBlanche( Compose(Compose(blanc, blanc, blanc, blanc), blanc, blanc, blanc)));
    printf("Image Noire (X) : %b\n", EstBlanche(noir));
    printf("Image avec du Noir (oXooX*Xo*) : %b\n", EstBlanche(Compose(blanc, Compose(noir, blanc, blanc, noir), noir, blanc)));
}


bool EstNoire(Image img){
    if (img == NULL){ 
        return TRUE; 
    } else if (img->quatre == FALSE) { 
        return FALSE; 
    } else { 
        return EstNoire(img -> hg) && EstNoire(img -> hd) && EstNoire(img -> bg) && EstNoire(img -> bd);
    }
}


void testEstNoire(){
    Image blanc = Blanc();
    Image noir = Noir();
    printf("\n~~~~ TEST EST NOIRE ~~~~\n");
    printf("Image Noire (X) : %b\n", EstNoire(noir));
    printf("Image Noire (XXXX*XXX*) : %b\n", EstNoire( Compose(Compose(noir, noir, noir, noir), noir, noir, noir)));
    printf("Image Blanche (X) : %b\n", EstNoire(blanc));
    printf("Image avec du Blanc (XoXXo*oX*) : %b\n", EstNoire(Compose(noir, Compose(blanc, noir, noir, blanc), blanc, noir)));
}


/*************************************************/
/*                                               */
/*                    Aire                       */
/*                                               */
/*************************************************/

float Aire(Image img){
    if (img == NULL){
        return 1.0;
    }else if (img -> quatre == FALSE){
        return 0.0;
    } else {
        return (Aire(img -> hg) + Aire(img -> hd) + Aire(img -> bg) + Aire(img -> bd)) / 4.0;
    }
}

void testAire() {
    Image noir = Noir();
    Image blanc = Blanc();
    
    printf("\n~~~~ TEST AIRE ~~~~\n");
    printf("Image X : %.2f\n", Aire(noir));
    
    Image img = Compose(noir, Compose(blanc, noir, blanc, blanc), noir, Compose(noir, noir, noir, blanc));
    printf("Image XoXoo*XXXXXo** : %.2f\n", Aire(img));
    
}


/*************************************************/
/*                                               */
/*                 TriangleBD                    */
/*                                               */
/*************************************************/

Image TriangleBD(int p){
    if (p == 0){
        return Blanc();
    } else {
        Image tmp = TriangleBD(p-1);
        return Compose(Blanc(), tmp, tmp, Noir()); 
    }
}


void testTriangleBD(){
    
    printf("\n~~~~ TEST TRIANGLEBD ~~~~\n");
    printf("Triangle p = 0 (resultat attendu : o) : ");
    Affichage(TriangleBD(0));
    printf("\nTriangle p = 1 (resultat attendu : oooX*) : ");
    Affichage(TriangleBD(1));
    printf("\nTriangle p = 3 (resultat attendu : oooooX*oooX*X*ooooX*oooX*X*X*) : ");
    Affichage(TriangleBD(3));
    printf("\n");

}


/*************************************************/
/*                                               */
/*                 Arrondit                      */
/*                                               */
/*************************************************/

void Arrondit(Image *img, int p){
    if (*img != NULL){
        if (p > 0){
            Arrondit(&((*img) -> hg), p-1);
            Arrondit(&((*img) -> hd), p-1);
            Arrondit(&((*img) -> bg), p-1); 
            Arrondit(&((*img) -> bd), p-1);
        } else {
            if (Aire(*img) > 0.5){ *img = Noir(); }
            else { *img = Blanc(); }
        }
    }
}


void testArrondit(){
    Image noir = Noir();
    Image blanc = Blanc();
    
    Image img = Compose(noir, Compose(Compose(noir, Compose(noir, blanc, blanc, noir), Compose(blanc, noir, noir, blanc), Compose(blanc, blanc, blanc, noir)), blanc, noir, blanc), blanc, Compose(noir, Compose(noir, blanc, blanc, Compose(blanc, noir, noir, noir)), blanc, noir)); 
    
    printf("\n~~~~ TEST ARRONDIT ~~~~\n");
    printf("Résultat attendu :XXoXo*oXooX**, résultat calculé : ");
    Arrondit(&img, 2);
    Affichage(img);
    printf("\n");

}


/*************************************************/
/*                                               */
/*                 MemeDessin                    */
/*                                               */
/*************************************************/

bool MemeDessin(Image img1, Image img2){
    if (img1 == NULL)                   { return EstNoire(img2); }
    else if (img2 == NULL)              { return EstNoire(img1); }
    else {
        if (img1->quatre == FALSE)      { return EstBlanche(img2); }
        else if (img2->quatre == FALSE) { return EstBlanche(img1); }
        else {
            return MemeDessin(img1->hg, img2->hg) && MemeDessin(img1->hd, img2->hd) && MemeDessin(img1->bg, img2->bg) && MemeDessin(img1->bd, img2->bd);
        }
    }
}

void testMemeDessin(){
    Image blanc = Blanc();
    Image noir = Noir();

    Image img1 = Compose(noir, Compose(blanc, Compose(Compose(blanc, blanc, blanc, blanc), blanc, blanc, blanc), Compose(blanc, blanc, blanc, blanc), blanc), noir, Compose(blanc, blanc, blanc, Compose(noir, noir, noir, noir)));
    
    Image img2 = Compose(noir, blanc, noir, Compose(blanc, blanc, blanc, noir));
    
    printf("\n~~~~ TEST MEMEDESSIN ~~~~\n");
    printf("Test avec deux Images équivalentes : %b\n", MemeDessin(img1, img2));
    
    Image img3 = Compose(noir, blanc, noir, Compose(noir, blanc, blanc, blanc));
    printf("Test avec deux Images non équivalentes : %b\n\n", MemeDessin(img1, img3));
    

}

/*************************************************/
/*                                               */
/*                 InterUnion                    */
/*                                               */
/*************************************************/

void InterUnion(Image *img1, Image *img2){
    if (*img1 == NULL){
        *img1 = *img2;            
        *img2 = Noir();
    } else if ((*img1)->quatre == TRUE && (*img2 != NULL)) {
        if ((*img2)->quatre == FALSE) {
            *img2 = *img1;
            *img1 = Blanc();
        } else if ((*img2)->quatre == TRUE) {
            InterUnion(&((*img1) -> hg), &((*img2) -> hg));
            InterUnion(&((*img1) -> hd), &((*img2) -> hd));
            InterUnion(&((*img1) -> bg), &((*img2) -> bg));
            InterUnion(&((*img1) -> bd), &((*img2) -> bd)); 
        }
    }
}

void testInterUnion(){
    Image noir = Noir();
    Image blanc = Blanc();
    
    Image img1 = Compose(blanc, noir, Compose(blanc, noir, noir, blanc), Compose(Compose(blanc, noir, blanc, noir), blanc, noir, noir));
    Image img2 = Compose(noir, blanc, noir, Compose(blanc, Compose(noir, blanc, blanc, noir), Compose(blanc, blanc, noir, noir), noir));
    
    printf("\n~~~~ TEST INTERUNION ~~~~\n");
    printf("Image de l'énoncé :  img1 ");
    Affichage(img1);
    printf(" | img2 : ");
    Affichage(img2);
    printf("\n Inter : ");
    InterUnion(&img1, &img2);
    Affichage(img1);
    printf("   -  Union : ");
    Affichage(img2);
    printf("\n");
}

/*************************************************/
/*                                               */
/*                 CompteDamiers                 */
/*                                               */
/*************************************************/

int CompteDamiers(Image img) {
    if (img == NULL || img->quatre == FALSE) {
        return 0;
    } else if ((img->hg)->quatre == FALSE && (img->bd)->quatre == FALSE && (img->hd)==NULL && (img->bg)==NULL) {
        return 1;
    }
    int damiers = CompteDamiers(img->hg) + CompteDamiers(img->hd) + CompteDamiers(img->bg) + CompteDamiers(img->bd);
    
    if (damiers % 4 == 0 && 
        (damiers / 4) == CompteDamiers(img->bd) && 
        (damiers / 4) == CompteDamiers(img->bg) && 
        (damiers / 4) == CompteDamiers(img->hd) &&  
        (damiers / 4) > 0) {
        return damiers + 1;
    }

    return damiers;
}

void testCompteDamiers(){
    Image noir = Noir();
    Image blanc = Blanc();
    Image damier = Compose(blanc, noir, noir, blanc);
    
    Image img = Compose(Compose(blanc, noir, noir, blanc), 
                        Compose(blanc, noir, noir, blanc), 
                        Compose(blanc, noir, noir, blanc), 
                        Compose(blanc, noir, noir, blanc));
    
    
    Image img2 = Compose(Compose(damier, damier, damier, damier), Compose(Compose(damier, damier, damier, damier), damier, damier, damier), Compose(damier, damier, noir, noir), Compose(Compose(blanc, blanc, blanc, blanc), noir, noir, Compose(blanc, blanc, Compose(blanc, blanc, blanc, blanc), blanc)));   
    // oXXo*oXXo*oXXo*oXXo**oXXo*oXXo*oXXo*oXXo**oXXo*oXXo*oXXo**oXXo*oXXo*XX*oooo*XXoooooo*o***!
    
    Image img3 = Lecture();
    
    printf("\n~~~~ TEST COMPTEDAMIERS ~~~~\n");
    printf("Image de l'énoncé img : ");
    Affichage(img);
    printf("\nCompte Damier : %d \n", CompteDamiers(img));
    
    printf("Image de l'énoncé img2 : ");
    Affichage(img2);
    printf("\nCompte Damier : %d \n", CompteDamiers(img2));
    
    printf("Image taper dans la console img3 : ");
    Affichage(img3);
    printf("\nCompte Damier : %d \n", CompteDamiers(img3));
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/
void mainTest(){
    testAffichage();
    testAffichageProfondeur();
    testEstBlanche();
    testEstNoire();
    testAire();
    testTriangleBD();
    testArrondit();
    testMemeDessin();
    testInterUnion();
    testCompteDamiers();
}


int main(int argc, char** argv) {

    mainTest();
    
    
    
    return 0;
}