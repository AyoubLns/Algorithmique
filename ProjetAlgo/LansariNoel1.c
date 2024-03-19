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

typedef enum { false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0)
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n)
{ long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/

float Efloat () { 
    // Initialisation de la somme à 1.0 (le premier terme de la série)
    float somme = 1.0;
    int i = 1;
    // Initialisation 0! = 1
    float facto = 1.0;

    // Boucle infinie (s'arrête lorsque 1/n! devient trop petit pour affecter la somme)
    while (1.0 / facto > 0.0) {
        // n! du terme suivant
        facto *= i;
        // Ajouter 1/n! à la somme
        somme += 1.0 / facto;
        i++;
    }
    return somme;
}

/*************************************************/

double Edouble() {
    double somme = 1.;
    // Initialisation de l'indice de la boucle et du facteur de calcul du factoriel
    int i = 1;
    double facto = 1.0;
    // Boucle de calcul de la série de Taylor pour 'e'
    while (1./facto > 0.) {
        // Calcul du factoriel
        facto *= i; 
        // Ajout du terme actuel à la somme
        somme += 1. / facto;
        i++;
    }
    return somme;
}

/*************************************************/

long double Elongdouble() {
    long double somme = 1.L;
    int i = 1;
    long double facto = 1.L;
    while (1.0L/facto > 0.) {
        facto *= i; 
        somme += 1.0L / facto;
        i++;
    }
    return somme;
}

/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

void afficheYfloat (int n) {
    printf("affiche yn (float) : \n");
    float yn = Efloat()-1;
    for(int i = 0; i<=n; i++){
        printf("y%d = %f \n", i, yn);
        yn = (i+1)* yn -1;
    }
}

/*************************************************/

void afficheYdouble (int n) {
    printf("affiche yn (double) : \n");
    double yn = Edouble()-1;
    for(int i = 0; i<=n; i++){
        printf("y%d = %lf \n", i, yn);
        yn = (i+1)* yn -1;
    }
}

/*************************************************/

void afficheYlongdouble (int n) {
    printf("affiche yn (long double) : \n");
    long double yn = Elongdouble()-1;
    for(int i = 0; i<=n; i++){
        printf("y%d = %Lf \n", i, yn);
        yn = (i+1)* yn -1;
    }
}

/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/

double power1 (double x, long n) { 
    if (n == 0){
        return 1.0;
    } else if (n > 0){
        return power1(x, n-1) * x;
    } else {
        return 1./power1(x, -n);
    }
}

/*************************************************/

double power2a (double x, long n) {
    if (n == 0){
        return 1.0;
    }
    double res = 1.0;
    for(int i = 1; i<=n; i++){
        res = res * x;
    }
    return res;
    
}

/*************************************************/

double power2b (double x, long n) { 
    if (n == 0){
        return 1.0;
    }
    double res = 1.0;
    while(n>0){
        res = res * x;
        n--;
    }
    return res;
}

/*************************************************/

void pow3(double x, long n, double *res) {
    if (n != 0) {
        *res = *res * x;
        pow3(x, n - 1, res);
    }
}

double power3(double x, long n) {
    double res = 1.0;
    pow3(x, n, &res);
    return res;
}

/*************************************************/

double pow4(double x, long n, double res){
    if(n != 0){
        return pow4(x, n-1, res * x);
    }
    return res;
}

double power4 (double x, long n) { 
    return pow4(x, n, 1.0);
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m

double power5 (double x, long n)
{
    if (n == 0) 
        return 1 ;
         else if (n % 2 == 0)
              return (power5(x,n/2)*power5(x,n/2)   ) ;
         else return (power5(x,n/2)*power5(x,n/2) *x) ;   
}

/*************************************************/

double power6 (double x, long n) { 
    if(n != 0){
        double y = power6(x, n/2);
        if(n % 2 == 0){
            return y * y;
        }else{
            return y * y * x;
        }
    }
    return 1.0;
}

/*************************************************/

double power7 (double x, long n) { 
    if(n != 0){
        if(n % 2 == 0){
            return power7(x*x, n/2);
        }else{
            return power7(x*x, n/2) * x;
        }
    }
    return 1.0;
}

/*************************************************/

double pow8(double x, long n, double res){
    if(n != 0){
        if(n % 2 == 0){
            return pow8(x*x, n/2, res);
        }else{
            return pow8(x*x, n/2, res*x);
        }
    }
    return res;
}

double power8 (double x, long n) { 
    return pow8(x, n, 1.0);
}

/*************************************************/

void pow9(double x, long n, double *res){
    if(n ISNOT 0){
        if(n % 2 ISNOT 0){
            *res = *res * x;
            pow9(x, n - 1, res);
        }else{
            pow9(x*x, n/2, res);
        }
    }
}

double power9 (double x, long n) { 
    double res = 1.0;
    pow9(x, n, &res);
    return res;
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat

double power10 (double x, long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

double power (double x, long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ; break ;
   case 2 : return power2a(x,n) ; break ;  // 2 pour 2a
   case 0 : return power2b(x,n) ; break ; // 0 pour 2b
   case 3 : return power3(x,n) ; break ;
   case 4 : return power4(x,n) ; break ;
   case 5 : return power5(x,n) ; break ;
   case 6 : return power6(x,n) ; break ;
   case 7 : return power7(x,n) ; break ;
   case 8 : return power8(x,n) ; break ;
   case 9 : return power9(x,n) ; break ;
  case 10 : return power10(x,n) ; break ;
     default : return 0 ; 
   }
}

   // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/

    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

long double power11 (long double x, long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

float power12 (float x, long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}


/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/


int A1(int m, int n) { 
    if(m == 0){
        return n+1;
    }else{
        if(n == 0){
            return A1(m-1, 1);   
        }else{
            return A1(m-1, A1(m, n-1)); 
        }
    }
}

int Ackermann1 (int m) { 
    return A1(m, 0); 
}

/*************************************************/

int A2(int m, int n) {
    if(m == 0){
        return n+1;
    }else{
        int res = 1;
        for(int i = 0; i < n+1; i++){
            res = A2(m-1, res);
        }
        return res;
    }
}

int Ackermann2 (int m) { 
    return A2(m, 0); 
}

/*************************************************/

int A3(int m, int n) {
    for(int i = m; i > 0; i--){
        if(n == 0){
            n = 1;  
        }else{
            n = A3(i, n-1); 
        }
    }
    return n+1;
}

int Ackermann3(int m){
    return A3(m, 0);
}

/*************************************************/

/* 
int A4 (int m, int n) { 
    int res;
    if(m==0){
        res = n+1;
    }
    while(m != 0){
        for(int i = 0; i < n+1; i++){
            
        }
        m--;
    }
    return res;
}
*/

int Ackermann4 (int m) { 
    return 0; 
}

/*************************************************/

int Ackermann5 (int m) { return 0 ; }

/*************************************************/
  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : return Ackermann1 (m) ; // break ;
   case 2 : return Ackermann2 (m) ; // break ;
   case 3 : return Ackermann3 (m) ; // break ;
   case 4 : return Ackermann4 (m) ; // break ;
   case 5 : return Ackermann5 (m) ; // break ;
   default : return 0 ; 
   }
}

/*************************************************/
/*                                               */
/*             Suite d'entier X(n)               */
/*                                               */
/*************************************************/

int LN2Iter(int n){
    int cpt = 0;
    while(n != 1){
        n = n/2;
        cpt++;
    }
    return cpt;
}

int LN2Rec(int n){
    if( n==1 ){
        return 0;
    }else{
        return 1 + LN2Rec(n/2);
    }
}

int SuiteXIter(int n){
    int x = 2;
    for(int i = 0; i<n; i++){
        x = x + LN2Iter(x);
    }
    return x;
}

int SuiteXRec(int n, int x){
    if( n==0 ){
        return x;
    }else{
        return SuiteXRec(n-1, x + LN2Rec(x));
    }
}

int SXaux1(int n, int res){
    if( n==0 ){
        return res;
    }else{
        return SXaux1(n-1, res + LN2Rec(res));
    }
}

int SuiteXRecFonc(int n){
    return SXaux1(n, 2);
}

void SXaux2(int n, int *res) {
    if (n > 0) {
        *res = *res + LN2Rec(*res);
        SXaux2(n - 1, res);
    }
}

int SuiteXRecProc(int n) {
    int x = 2;
    SXaux2(n, &x);
    return x;
}


/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{

       double x ;
       long double y ;
       float z ;
       
       int cptx ;
  
       long nx ;
       
       int i,j ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (true) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (true) {     
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (true) {

     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (true) {  
       

        printf(" e1 = %.20f \n", Efloat()) ;
        printf(" e2 = %.30lf \n", Edouble()) ; 
        printf(" e3 = %.40Lf \n", Elongdouble()) ; 
        printf("\n") ; 
        
}

if (true) {  
            afficheYfloat(30) ; 
            printf("\n") ;
            afficheYdouble(30) ;
            printf("\n") ;
            afficheYlongdouble(30) ;    
            printf("\n") ;
}
        
/******************    power     *******************************/

if (true) {  

        //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
        
        for(i=0 ; i<=10 ; i++)
        printf("Power %d dit que power(2,10) vaut %.0lf \n", i, power(2,10,i) ) ;
        
        printf("\n") ;
      
}

        
if (false) {  

        i=5 ;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++)
        {
        printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;
       
}
     
if (false) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;



}

/******************    Ackermann    *******************************/
                
if (false) { 
 
        for(i=1 ; i<=5 ; i++)  // numéro de version
        
        for(j=0 ; j<=5 ; j++)  // test de A(j,0) pour j de 0 à 5
        
        printf("Ack%d(%d) = %d \n", i, j, Ackermann(j,i)) ;
}

/***********************************************************************/
 
/******************    SuiteX    *******************************/
if (true) { 

    int n = 100;

    printf("SuiteXIter(%d) = %d \n", n, SuiteXIter(n)) ;

    printf("SuiteXRec(%d) = %d \n", n, SuiteXRec(n, 2)) ;

    printf("SuiteXRecFonc(%d) = %d \n", n, SuiteXRecFonc(n)) ;

    printf("SuiteXRecProc(%d) = %d \n", n, SuiteXRecProc(n)) ;
}
/***********************************************************************/

    return 0;
}
