#ifndef _Math++_H_
#define _Math++_H_
#include <limits.h>
#include <math.h>


long int Max(long int a,long int b){
    if (a<b) return b;
        else return a;
}
long int Min(long int a,long int b){
    if (a>b) return b;
        else return a;
}
long int rand_a_b (long int a,long int b){ /// Random number in [a,b]
    long int k=(rand()*32011+rand());
    return (k%(Max(a,b)-Min(a,b)+1)+Min(a,b));
}
int Annee_bissextile(int year){
    return ((year%400==0)||((year%4==0)&&(year%100!=0)));
}
int maxjour(int y,int m){

    /** DONNEZ LE MAXIMAN JOUR DE LA MOIS
     ** IL PRENDS COMPS LE ANNES DES 29 ET 28 FIVIRIER
     **/

     switch (m) {

     case 1: return 31;
     case 2: return Annee_bissextile(y) ? 29 : 28 ;
     case 3: return 31;
     case 4: return 30;
     case 5: return 31;
     case 6: return 30;
     case 7: return 31;
     case 8: return 31;
     case 9: return 30;
     case 10: return 31;
     case 11: return 30;
     case 12: return 31;

     }
}




#endif
