#include "stdio.h"
#include "stdlib.h"
#include "Headers/Block.h"
#include "string.h"
#include <time.h>
#include <openssl/sha.h>

//7.1
//prend un block et l'écrit dans un fichier
void write_block(char* nom,Block *b){
  
  FILE *bf=fopen(nom,"w");
  if (bf==NULL){printf("Erreur d'ouverture\n");}
  char *auteur =key_to_str(b->author);
  //on choisit un format : 
  fprintf(bf,"Cle de l'auteur : %s \nvaleur hachee : %s \nvaleur precedente hachee %s \npreuve de travaille : %d \n",auteur,b->hash,b->previous_hash,b->nonce);
  CellProtected *tmp = b->votes; 
  char *votes;
  //et on ecrit a la suite tout les protected.
  while(tmp){
    votes=protected_to_str(tmp->data);
		fprintf(bf,"%s\n",votes);
		tmp=tmp->next;
    free(votes);    
	}
                
	free(auteur);
  fclose(bf);
}

//7.2
//prend un fichier formaté et l'écrit dans un bloc
Block* file_to_block(char* Nom){
    FILE *bf=fopen(Nom,"r");
    if (bf==NULL)
    {
      printf("Erreur d'ouverture\n");
    }
    Block *b=(Block*)calloc(1,sizeof(Block));
    if (!b){printf("Erreur d'allocation");}
    char chaine[256] = "";
    char tmp[256] = "";

    // Cle de l'auteur :  
    fgets(chaine,256,bf);
    sscanf(chaine,"Cle de l'auteur : %s",tmp);
    b->author=str_to_key(tmp);

    // Valeur hache :
    fgets(chaine,256,bf);
    sscanf(chaine,"valeur hachee : %s",tmp);
    b->hash=(unsigned char*)strdup(tmp);
    
    // Valeur hache precedent:
    fgets(chaine,256,bf);
    sscanf(chaine,"valeur precedente hachee  %s",tmp);
    if(strcmp(tmp, "(null)")==0){
       b->previous_hash=NULL;
    }
    else
    {
      b->previous_hash=(unsigned char*)strdup(tmp);
    }
  
    //preuve de travaille :
    fgets(chaine,256,bf);
    sscanf(chaine,"preuve de travaille : %d",&b->nonce);
   
    Protected *tmp2 = NULL;
  //on s'occupe des votes
    while(fgets(chaine,255,bf)!= NULL){
      tmp2=str_to_protected(chaine);
      ajout_en_tete_cpr(&b->votes,create_cell_protected(tmp2));
    }

    fclose(bf);
    return b;
}

//7.3
// transforme un bloc en chaine de caractère 
char* block_to_str(Block* block){

  char str[11]; //int en char au prend 11 de place.
  char *auteur = key_to_str(block->author);
  char *charfinal = (char*)calloc(sizeof(char),10000); 
  if(!charfinal) printf("Erreur d'allocation \n");
  charfinal[0] = '\0';
  strcat(charfinal,auteur);
  strcat(charfinal,"\n");
  //on verifie si le block precedent existe ou non 
  if(block->previous_hash){
    strcat(charfinal,block->previous_hash);
  }else{
    strcat(charfinal,"(null)");
  }

  strcat(charfinal,"\n");
  CellProtected * tmp = block->votes;
  char *votes;

  //on print tout les protected 
  while(tmp){
    votes = protected_to_str(tmp->data);
    strcat(charfinal,votes);
    strcat(charfinal,"\n");
    free(votes);
    tmp = tmp->next;  
     
  } 
  
  sprintf(str, "%d", block->nonce);
  strcat(charfinal,str);
  strcat(charfinal,"\n");
  
  free(auteur);
  
  return charfinal;
  
}

//7.5
//Prends une chaine de caractère et la chiffre
unsigned char* str_to_SHA256(char *str) {

  unsigned char *tab = (unsigned char *)malloc(256 * sizeof(unsigned char));
  if (tab == NULL) {
    printf("Erreur d'allocation");
  }
  tab[0] = '\0';
   unsigned char *d = SHA256(str, strlen(str), 0);
   unsigned char tmp[16];

  //on fait le proceder dans le main donner 
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    sprintf(tmp, "%02x", d[i]);
    strcat(tab, tmp);
  }

  return tab;
}


//7.6
void compute_proof_of_work(Block *B, int d) {
  B->nonce = 0;
 
  if (B->hash == NULL) {
    char *str = block_to_str(B);
    B->hash = str_to_SHA256(str); //On initialise la valeur de B->hash avec la valeur hache du block
    free(str);
  }
  unsigned char tmp[256];
  unsigned char nonce[11];

  sprintf(nonce, "%d", B->nonce);
  strcpy(tmp, B->hash);
  strcat(tmp, nonce);
  unsigned char *valeurhache = str_to_SHA256(tmp); 

  
  //on compte le nombre de d consecutif au debut de valeurhache
  int compteur = 0;
  while (compteur < d) {
    if (valeurhache[compteur] == '0') {//On regarde le nombre de 0 sinon on rehache le block et on ressaye  
      compteur++;
    }
    else {
      B->nonce++;
      compteur = 0;
      free(valeurhache);
      sprintf(nonce, "%d", B->nonce);
      strcpy(tmp, B->hash);
      strcat(tmp, nonce);
      valeurhache = str_to_SHA256(tmp);
    }
  }
  printf("La preuve de travaille : %d et sa valeur hache %s\n", B->nonce, valeurhache);
  free(valeurhache);
}

//7.7
//On vérifie si un block est valide
int verify_block(Block* b, int d){
  
  char chaine[256];
  char tampon [16] ;
  strcpy(chaine,b->hash);
  
  sprintf (tampon, "%d",b->nonce) ;
  
  strcat(chaine,tampon);
  unsigned char* tab=str_to_SHA256(chaine);
  for(int i= 0;i<d;i++){
       if(tab[i]!='0')
        return 0; 
  }
  free(tab);
  return 1;

}


void creerfichierblock(Block *B,int d){

  FILE *f=fopen("Comparaison2.txt","w");
	clock_t temps_initial,temps_final;
	double 	temps_cpu;

	if( (f) != NULL ) {
		
		for( long i = 1 ;i<= d ; i+=1 ){
			//On prend le temps mis pour l'execution de mod_naive(a,i,n)
			temps_initial=clock();
			compute_proof_of_work(B,i);
			temps_final=clock();

			//on convertit les "ticks consommes par modpow_naive en secondes"
			temps_cpu=((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;


			fprintf(f,"%ld %f \n",i,temps_cpu);
		}
	} else{
		printf("erreur\n");
	}
	fclose(f);
}

//libère l'espace mémoire d'un bloc
void delete_block(Block*b){

  if (b==NULL) { fprintf(stderr,"Error: delete_block, block null\n"); return;};
  free(b->author);
  delete_liste_pr(b->votes);

  free(b->hash);
  free(b->previous_hash);
  free(b);
  
}




  

