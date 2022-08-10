#include <stdio.h>	
#include <stdlib.h>
#include "Headers/src.h"
#include "Headers/key.h"


//2.1
// nous permet de générer le couple de clé (s,n) et (u,n) à partir de deux nombres premiers p et q
void generate_key_values (long p, long q, long* n, long* s, long* u)
{
    *n = (p * q);
    long t = (p - 1) * (q - 1);
    *s = rand_long(0, t);
    long v;
    long gcd = extended_gcd(*s, t, u, &v);
    if (gcd != 1) {
		generate_key_values(p, q, n, s, u);
	}
}

//3.2
//Initialise les valeurs d'une clé déjà allouée en mémoire
void init_key(Key* key, long val, long n)
{
	if(key == NULL){
		printf("La cle est nulle");
		return;
	}

	key->val = val;
	key->n = n;
	
	if(key->val != val || key->n != n){
		printf("Erreur d'affectation des valeurs des cles" );
	}

}

//3.3
//initialise directement deux clés déjà allouée afin d'en faire un couple Skey et Pkey
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size){

	long p = random_prime_number(low_size, up_size, 5000);
	long q = random_prime_number(low_size, up_size, 5000);

	while(p == q){
		
	 p = random_prime_number(low_size, up_size, 5000);
	}
	long n ,s ,u;
	generate_key_values(p, q, &n, &s, &u );
	 //Pour avoir des cles positives :
 	if (u <0) {
 	long t = (p -1) *( q -1) ;
 	u = u + t ; //on aura toujours s*u mod t = 1
 }	
	init_key(pKey, s, n);
	init_key(sKey, u, n);

}

//3.4
//convertit en chaine de caractères une clé afin de stocker dans un fichier
char* key_to_str(Key* key){
	char* tab = (char*) malloc(sizeof(char) *256);
	if(tab == NULL){
		printf("Erreur d allocation");

		return NULL;
	}
	sprintf(tab, "(%lx,%lx)", key->val, key->n);

	return tab;

}

//3.4
//convertit une chaine de caractère au bon format en clé, pour extraire d'un fichier texte
Key* str_to_key(char* str){
    long val;
    long n;
    if(sscanf(str, "(%lx,%lx)", &val, &n) == 2){
        //free(str);
        Key *key = (Key*)malloc(sizeof(Key)); //allocation de mémoire
        if(!key){ //vérification de l'allocation
            printf("Erreur pendant l'allocation\n");
            return NULL;
        }
        key->val = val;
        key->n = n;
        return key;
    }
    else{
        printf("Erreur de formatage\n");
        return NULL;
    }
}


Key *create_key() {
  Key *key = (Key *) malloc(sizeof(Key));

  if (key == NULL){
    printf("Erreur d'allocation\n");
  }

  return key;
}