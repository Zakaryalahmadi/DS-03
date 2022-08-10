#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include <string.h>
#include "Headers/signature.h"
#include "Headers/src.h"
#include "Headers/Protected.h"
#include "Headers/Block.h"
#include "Headers/Votes.h"
#include <openssl/sha.h>
#include <dirent.h>

#define SIZEV 2000
#define SIZEC 50
#define POW 3


int main(void){


 //PARTIE 1

printf("________________________________PARTIE 1__________________________________________\n \n");
//Question 1.1


//question 1.


	//Q1.1
	/*unsigned long p1 = 3;
	int res=1;
	clock_t t_ini;
	clock_t t_fin;
	double t_cpu=0;
	while((t_cpu<2.0)||res==1){
		t_ini= clock();
		res = is_prime_naive(p1);
		t_fin =clock();
		t_cpu = ((double)(t_fin-t_ini))/CLOCKS_PER_SEC;
		printf("t_cpu = %.10f | \n",t_cpu);
		p1+=112345677;
	}
	printf("p = %ld, t_cpu = %.2f",p1,t_cpu); 

	
	//Q1.2
	long test12 = modpow_naive(113,2,41);
	printf("Pour modpow_naive : %ld\n",test12);
	
	//Q1.3
	long test13 =modpow(113,2,41);
	printf("Pour modpow : %ld\n",test13);
	//Q1.5
	creerfichier(2,10000,4);
	//plot "courbe.txt" using 1:2 title 'modpow_naive' with lines
	//replot "courbe.txt" using 1:3 title 'modpow' with lines
 */

//Q 1.8

int low_size = 10;
int up_size  = 100;
int Miller = 20;

printf("Le nombre premier de taille compris entre %d et %d est %ld avec %d tests de Miller à réaliser \n ",low_size,up_size,random_prime_number(low_size,up_size,20),Miller);


srand ( time ( NULL ) ) ;

 //Generation de cle :
 long p = random_prime_number (5 ,7 , 5000) ;
 long q = random_prime_number (5 ,7 , 5000) ;
 
 while ( p == q ) {
 q = random_prime_number (5 ,7 , 5000) ;
 }
 long n , s , u ;
 generate_key_values (p ,q ,&n ,&s ,&u ) ;

 //Pour avoir des cles positives :
 if (u <0) {
 long t = (p -1) *( q -1) ;
 u = u + t ; //on aura toujours s*u mod t = 1
 }	

 //Afichage des cles en hexadecimal
 printf ("cle publique = (%lx , %lx ) \n" ,s , n ) ;
 printf ("cle privee = (%lx , %lx ) \n" ,u , n ) ;

 //Chiffrement:
 char mess[10] = "Hello" ;
 int len = strlen ( mess ) ;
 long* crypted = encrypt ( mess , s , n ) ;

printf ( "Initial message : %s \n" , mess ) ;
printf ( " Encoded representation : \n" ) ;
 print_long_vector ( crypted , len ) ;

//Dechiffrement
char* decoded = decrypt ( crypted , len , u , n ) ;
printf ( "Decoded : %s \n" , decoded ) ;

free(decoded);
free(crypted);	


//Partie 2

printf("________________________________PARTIE 2__________________________________________\n \n");
//Testing Init Keys
Key *pKey = malloc (sizeof ( Key ) ) ;
Key *sKey = malloc ( sizeof ( Key ) ) ;
init_pair_keys ( pKey , sKey ,3 ,7) ;
printf ( "pKey : %lx , %lx \n" , pKey->val , pKey->n ) ;
printf ( "sKey : %lx , %lx \n" , sKey->val , sKey->n ) ;	


//Testing Key Serialization

char *chaine2 = key_to_str ( pKey ) ;
 printf ( "key to str : %s \n" , chaine2 ) ;
 Key *k = str_to_key ( chaine2 ) ;
 printf ( "str to key : %lx , %lx \n" , k->val , k->n) ;
 free(k);
 //Testing signature
 //Candidate keys:
 Key *pKeyC = malloc ( sizeof ( Key ) ) ;
 Key *sKeyC = malloc ( sizeof ( Key ) ) ;
 init_pair_keys ( pKeyC , sKeyC ,3 ,7) ;
 //Declaration:
 char *mess2 = key_to_str ( pKeyC ) ;
 char *mess3 = key_to_str ( pKey ) ;
 printf ( "%s vote pour %s \n" , mess3 , mess2 ) ;
 Signature *sgn = sign ( mess2 , sKey ) ;

 
 printf ( "signature :" ) ;
 print_long_vector ( sgn->mess , sgn->taille) ;

free(chaine2);
free(mess3);

 char* chaine = signature_to_str ( sgn ) ;
 delete_signature(sgn);

 printf ("signature to str : %s \n" , chaine ) ;


 sgn = str_to_signature ( chaine ) ;
 printf ("str to signature : " ) ;
 print_long_vector( sgn->mess , sgn->taille ) ;
 free(chaine);



 //Testing protected:
 printf("mess2 : %s\n",mess2);
 Protected *pr = init_protected ( pKey , mess2 , sgn ) ;

 //Verification:
 if ( verify ( pr ) ) {
 printf ( " Signature valide \n" ) ;
 } else {
 printf ( "Signature non valide \n" ) ;
 }
 chaine = protected_to_str ( pr ) ;
 printf ( "protected to str : %s \n" , chaine ) ;
 free(pr);
 free(pr->mess);
 free(mess2);
 pr = str_to_protected( chaine ) ;
 mess2 = key_to_str ( pr->k );
 mess3 = signature_to_str ( pr->s);	
 printf ( "str to protected : %s %s %s \n" , mess2,pr->mess , mess3 ) ;
 delete_protected(pr);


 free(mess2);
 free(mess3); 
 free(chaine);
delete_signature(sgn);
 
 free ( pKey ) ;
 free ( sKey ) ;
 free ( pKeyC ) ;
 free ( sKeyC ) ;


printf("________________________________PARTIE 3__________________________________________\n \n");
	
CellKey *test = read_public_keys("keys.txt");
print_list_keys(test);
delete_liste_key(test);
generate_random_data(100,25);
CellProtected* test2 = read_protected("declarations.txt");	
fraudverif(&test2);
print_list_pr(test2);
delete_liste_pr(test2);


printf("________________________________PARTIE 4__________________________________________\n \n");

int nbcitoyens = 50;
int nbcandidats = 10;
CellKey *voters = read_public_keys("keys.txt"); 
CellKey *candidates = read_public_keys("candidates.txt");
   

    CellProtected *cp2 = read_protected("declarations.txt");
    puts("");
    fraudverif(&cp2);
    
	print_list_pr(cp2);
	//print_list_keys(candidates);
	//print_list_keys(voters);
    Key* test_compute = compute_winner(cp2, candidates, voters, nbcandidats, len_cellprotected(cp2));
	
    puts("\nVoici sa clé publique :");
    char* test1 = key_to_str(test_compute);
    printf("%s\n", test1);
    free(test1);
    free(test_compute);
	delete_liste_pr(cp2);
	
    delete_liste_key(voters);
    delete_liste_key(candidates);
printf("________________________________PARTIE 5__________________________________________\n \n");	


	printf("Avec le main du sujet :\n");
	const char* s2 = "Rosetta code" ;
	unsigned char * d = SHA256(s2 , strlen ( s2 ),0) ;
	int i ;
	for ( i = 0; i < SHA256_DIGEST_LENGTH ; i ++)
	printf ( "%02x" , d[i]) ;
	putchar ( '\n' ) ;

	printf("Avec notre fonction str_to_SHA256 :\n");
	unsigned char* a= str_to_SHA256("Rosetta code");
	
	for ( i = 0; i < SHA256_DIGEST_LENGTH ; i ++)
	printf ( "%02x" , a[i]) ;
	putchar ( '\n' ) ;
	free(a);

	Block *block=file_to_block("block.txt");
	write_block("Block.txt",block);
	char *blockstr=block_to_str(block);
	printf("le blocktostr : \n%s\n",blockstr);
	free(blockstr);
	compute_proof_of_work(block,3);
	printf("%d\n",verify_block(block,3));
	creerfichierblock(block,2);	
	//plot "Comparaison2.txt" using 1:2 title 'd' with lines
	delete_block(block);
	
	
		DIR *rep = opendir("Blockchain");
		if(rep!=NULL){
		struct dirent *dir ;
			while (( dir = readdir(rep) ) ) {
				if ( strcmp ( dir->d_name , "." ) !=0 && strcmp( dir->d_name , "..") !=0) {
				//printf ( "Chemin dufichier:./ Blockchain/ %s \n",dir-> d_name ) ;
			}
			}
		
	closedir(rep);
		}
	

	generate_random_data(1000, 5);

	CellProtected *decl = read_protected("declarations.txt");
	CellKey *candidate = read_public_keys("candidates.txt");
	CellKey *voter = read_public_keys("keys.txt");

		CellProtected *tmp = decl;
		CellTree *t = NULL,*tmp2;
		int compteur = 0;
		int nom = 0;
		char nomdefichier[256]="\0";
		char nomdefichier2[256]="\0";
		char nbfichier[11];
		i=1;

		while (tmp){
			submit_vote(tmp->data);
			compteur++;
			if(compteur%10 == 0){
				create_block(t,(tmp->data)->k,3);	
				sprintf(nbfichier, "%d",i++);
				strcat(nomdefichier2,nbfichier);
				strcat(nomdefichier2,".txt");
				add_block(3,nomdefichier2);

				if(!t){
					strcat(nomdefichier,"./Blockchain/");
					strcat(nomdefichier,nomdefichier2);
					t= create_node(file_to_block(nomdefichier));
					nomdefichier[0] = '\0';

				}
				else{
					tmp2=t;
					while(tmp2->firstChild != NULL){
						tmp2=tmp2->firstChild;
					}
					strcat(nomdefichier,"./Blockchain/");
					strcat(nomdefichier,nomdefichier2);
					add_child(tmp2,create_node(file_to_block(nomdefichier)));
					nomdefichier[0] = '\0';
					
				}

				nomdefichier2[0] = '\0';

			}
		
	
			tmp=tmp->next;
		}
	
	CellTree *tree = read_tree();
	print_tree(tree);
	Key *winner = compute_winner_BT(tree, candidate, voter, 2010, 60);
	char *str = key_to_str(winner);
	printf("La cle du vainqueur : %s\n", str);

free(str);
free(winner);
delete_tree(tree);
delete_tree(t);
delete_liste_key(candidate);
delete_liste_key(voter); 	
delete_liste_pr(decl);


return 0;


}




		
