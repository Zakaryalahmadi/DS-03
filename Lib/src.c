#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Headers/src.h"

//fonction renvoyant 1 si le nombre passé en paramètre est premier, 0 sinon
//compléxité en O(p)
int is_prime_naive(long p){
	//compléxité en O(p)
	for(int i=3;i<p;i++){//on teste pour chaque n>3 et n<p si n divise p 
		if(p%i==0){
		//p est divisible par i
			return 0;
		}
	}
	printf("%ld premier\n",p);
	return 1;
}


//Question 1.3
//fonction renvoyant a puissance m modulo p 
//compléxité en O(m)
long modpow_naive(long a, long m,long n){
	long res=1;
	for(int i =1;i<=m;i++){
		res*=a;
        res=res%n;
	}
	return res;
}


//Question 1.4
//fonction renvoyant a puissance m modulo p
//compléxité en O(log2(m)) 
long modpow(long a, long m, long n){
    long b = 0;
    if(m == 0){
        return 1;
    }
    else if(m%2 == 0){
        b = modpow(a, m/2, n);	
        return (b*b)%n;
    }
    else{ 	
        b = modpow(a, (int)(m/2), n);
        return (a*b*b)%n;
    }
}
//Question 1.5
//fonction permettant de tester le temps de calcul des fonctions précédentes
void creerfichier(long a,long m,long n){

    FILE *f=fopen("Comparaison.txt","w");

	clock_t temps_initial,temps_final,temps_initial2,temps_final2;
	double 	temps_cpu,temps_cpu2;

	if( (f) != NULL ) {
		
		for( long i = 0 ;i< m ; i+=100 ){
			//On prend le temps mis pour l'execution de mod_naive(a,i,n)
			temps_initial=clock();
			modpow_naive(a,i,n);
			temps_final=clock();

			//on convertit les "ticks consommes par modpow_naive en secondes"
			temps_cpu=((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;

			//On prend le temps mis pour l'execution de modpow(a,i,n)
			temps_initial2=clock();
			modpow(a,i,n);
			temps_final2=clock();

			//on convertit les "ticks consommes par modpow en secondes
			temps_cpu2=((double)(temps_final2-temps_initial2))/CLOCKS_PER_SEC;


			fprintf(f,"%ld %f %f \n",i,temps_cpu,temps_cpu2);
		}
	} else{
		printf("erreur\n");
	}
	fclose(f);
}
	

//Question 1.6
//fonction fournie
int witness ( long a , long b , long d , long p ) {
	long x = modpow (a ,d , p ) ;
	if ( x == 1) {
		return 0;
		}
		for(long i = 0; i < b ; i++){
			if ( x == p-1) {
				return 0;
				}
				x = modpow (x,2,p);
			}
			return 1;
}

//fonction fournie
long rand_long(long low , long up) {
	 return rand ()%(up - low+ 1) + low ;
 }

//fonction fournie
int is_prime_miller ( long p , int k ) {
	if ( p == 2) {
		return 1;
		}
	if (!( p & 1) || p <= 1) { //on verifie que p est impair et different de 1
	return 0;
	}
	//on determine b et d :
	long b = 0;
	long d = p - 1;
	while (!( d & 1) ) { //tant que d n’est pas impair
	d = d /2;
	b = b +1;
	}
	// On genere k valeurs pour a, et on teste si c’est un temoin :
	long a ;
	int i ;
	for ( i = 0; i < k ; i ++) {
		a = rand_long(2 , p -1) ;
		if ( witness (a ,b ,d , p ) ) {
			return 0;
		}
	}
	return 1;
 }

 //Question 1.7
 /* 0.25^k car 0 succès sur k tentatives indépendantes et aléatoires avec p = 3/4 */

//Question 1.8
//renvoie un nombre premier aléatoire dont la taille est comprise en 2^low_size et 2^up_size 
//avec un test de miller on test k fois si le nombre est bien premier, on génère un nouveau long aléatoire jusqu'à ce qu'il soit premier
long random_prime_number(int low_size, int up_size, int k){
	long nb_alea=rand_long ( pow(2,low_size) , pow(2,up_size+1)-1 );

	while(is_prime_miller (nb_alea,k)!=1){
        nb_alea=rand_long ( pow(2,low_size) , pow(2,up_size+1)-1 );
		
	}
	return nb_alea;

}

//2.1
//fonction fournie
long extended_gcd ( long s , long t , long *u , long *v ) {
	if ( s == 0) {
		 *u = 0;
		 *v = 1;
		 return t ;
	}

	long uPrim , vPrim ;
	long gcd = extended_gcd (t%s,s, &uPrim ,&vPrim ) ;
	*u = vPrim -( t/s)*uPrim ;
	*v = uPrim;
 	return gcd ;
}

//2.2
//permet de chiffrer une chaine de caractères tel que chaque caractère c = c^s mod n 
//avec Skey = (s,n), Pkey = (u,n) [Protocole RSA]
long *encrypt(char* chaine, long s, long n){
    long* res= malloc(strlen(chaine)*sizeof(long));
    for(int i = 0; i<strlen(chaine);i++){
        res[i]= modpow((long)chaine[i],s,n);
        //printf("%ld,%c\n",res[i],chaine[i]);
    }

    return res ;
}
//2.3
//permet de déchiffrer un tableau de long tel que pour chaque entier n = n^u mod n
//avec Skey = (s,n), Pkey = (u,n) [Protocole RSA]
char* decrypt(long* crypted, int size, long u, long n){
    char* res= malloc((size*sizeof (char))+1);
    int i=0;
    while(i<size){
        res[i]= (char) modpow(crypted[i],u,n);
        
        i++;
    }
    res[i]='\0';

    return res;
}
//fonction qui rend la longueur d'un tableau de long
int tablen (long* tab)
{
    int i = 0;
    while (tab[i]){
        i++;
    }
    return i + 1;
}

//fonction fournie
void print_long_vector (long* result, int size)
{
    printf("Vector : [");
    for (int i = 0; i < size; i++){
        printf("%lx \t", result[i]);
    }
    printf("]\n");
}

//fonction pour faire un tri dans generate_random_data
int intComparator ( const void * first, const void * second ) {
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}

//fonction pour connaitre l'appartenance d'un entier dans un tableau
int is_in_tab(int* tab, int taille, int n){  
    for(int i = 0; i < taille; i++){
        if (tab[i] == n)
            return 1;
    }
    return 0;
}

//vide complètement une chaine de caractère
void mem_reset(char *buff, size_t n) {
    for (size_t i = 0; i < n; i++)
        buff[i] = '\0';
}

