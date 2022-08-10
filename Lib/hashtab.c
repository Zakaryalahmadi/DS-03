#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Headers/hashtab.h"



//6.2
//alloue et initialise en mémoire une cellule de table de hachage
HashCell* create_hashcell(Key* key){

    HashCell* h = (HashCell*)malloc(sizeof(HashCell));
    if (h==NULL){
    	printf("Erreur d'allocation\n");
    	return NULL;
    }
    h->key=key;
    h->val=0;
    
    return h;
    
}

//Notre fonction
//libère l'espace mémoire d'une cellule de table de hachage
void delete_hashcell(HashCell* hcell){
	if(!hcell) return;
	
	free(hcell);
}

//6.3
//fonction de hachage de notre table de hachage
int hash_function(Key* key,int size){
	if(!key){
		printf("clé NULL");
		return -1;
	}
	//printf("key : %s \n",key_to_str(key));
	float A= (sqrt(5)-1)/2;
	return (((int) (floor(size *((key->val)*A)-floor((key->val)*A)))% size));
}

//6.4
//qui cherche dans la table t s’il existe un element dont la cle publique est key. les collisions sont gerees par un probing lineraire 
int find_position(HashTable* t, Key* key){
	if(!key){printf("key NULL\n");return -1;}
	if(!t){printf("table NULL\n");return -1;}
	
	// on calcule f(val)
	unsigned int pos = hash_function(key, t->size);
	if (t->tab[pos] == NULL ||( t->tab[pos]->key->val==key->val && t->tab[pos]->key->n==key->n)){ 
		
		//on renvoie f(val) Si la position est libre ou si la clé se situe déjà à f(val)
			
		return pos;
	}
		
	unsigned int pos2;
	for(int i = 1; i<(t->size);i++){
		pos2 =(pos+i)%(t->size);
		// on parcours les cases suivantes jusqu'à trouver une case libre ou si la clé est déjà présente
		if( t->tab[pos2] == NULL){
			
			return pos2;
		}
		if(t->tab[pos2]->key==key){
			return pos2;
		}
	}
		
	return pos;
	}
	
//6.5
//alloue et initialise une table de hachage à partir d'une liste chainée de clés
HashTable* create_hashtable(CellKey* keys, int size){
	if(!keys){
		return NULL;
	}
	
	HashTable* res = malloc(sizeof(HashTable));
	if(!res) printf("Erreure d'allocation \n");
	res->tab= malloc((size+10) * sizeof(HashCell*));
	if(!(res->tab)) printf("Erreure d'allocation \n");
	for(int i=0;i<size;i++)
		{
			res->tab[i]=NULL;
		}
	res->size=size;
	CellKey* tmp = keys;
	int i = 1;
	while(tmp->next){
		i=i%3;
		
		int pos = find_position(res, tmp->data);
		
		if (!res->tab[pos])
			res->tab[pos] = create_hashcell(tmp->data);
		//printf("%d\n",i++);
		if(tmp){ 
			tmp=tmp->next;
			
		}
	}
	return res;
}
	
//6.6
//supprime l'espace mémoire d'une table de hachage sans libérer l'espace dédié aux clés 
void delete_hashtable(HashTable* htab){
	if(!htab){
		printf("table invalide\n");
		return;
	}
	for(int i = 0; i<htab->size; i++){
		delete_hashcell(htab->tab[i]);
		}
	free(htab->tab);
	free(htab);
}
		

//6.7
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV) {
  
  HashTable *hv = create_hashtable(voters, sizeV);
  HashTable *hc = create_hashtable(candidates, sizeC);

  Key *keyV, *keyC;
  int posV, posC;

  // On parcours les déclarations
  while (decl != NULL) {
    keyV = (decl->data)->k;
    posV = find_position(hv, keyV);

    // On vérifie que les électeurs existent et qu'ils n'ont pas votés
    if (((hv->tab)[posV] != NULL) && (((hv->tab)[posV])->val == 0)) {
      keyC = str_to_key((decl->data)->mess);
      posC = find_position(hc, keyC);

      // on vérifie que le candidat existe
      if ((hc->tab)[posC] != NULL) {
        // On ajoute un vote et on incrémente la valeur de l'électeur pour qu'il ne vote pas de nouveau
        ((hc->tab)[posC])->val += 1;
        ((hv->tab)[posV])->val = 1;
      }

      free(keyC);
    }

    decl = decl->next;
  }


  // on cherche le gagnant
  int max = 0;
  int position;
  Key *keyTmp;
  Key *keygagnant = create_key();

  while (candidates != NULL) {
    // on calcule la position des candidats dans la table
    position = find_position(hc, candidates->data);

    // si le candidat à plus de vote que celui en tête précedemment
	if(hc->tab[position]){
    	if (((hc->tab)[position])->val > max) {
      	max = ((hc->tab)[position])->val;
      	keyTmp = ((hc->tab)[position])->key;
      	init_key(keygagnant, keyTmp->val, keyTmp->n);
    	}
	}

    candidates = candidates->next;
  }

  delete_hashtable(hv);
  delete_hashtable(hc);

  return keygagnant;
}

	
	




		
		
		
		
		
		
		
		  
