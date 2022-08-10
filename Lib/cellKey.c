#include <stdio.h>
#include <stdlib.h>
#include "Headers/cellKey.h"
#include "Headers/key.h"


//5.1
CellKey* create_cell_key(Key* key){
	CellKey *res = malloc(sizeof(CellKey));
	if(!res){ //vérification de l'allocation mémoire
		printf("Echec d'allocation\n");
		return NULL;
	}
	res->data = key;
	res->next = NULL;
	return res;
}
	
//5.2
//ajout en tête d'une liste chainée
void ajout_en_tete_ckey(CellKey** lc, CellKey* key){
	if(!lc){
		*lc = key;
		return;
	}
	key->next =*lc;
	*lc = key;
} 

//5.3
//transformation d'un fichier formaté en une liste chainée de clés
CellKey* read_public_keys(char* nomFich){
	char ligne[256];
	Key *tmp = NULL;
	CellKey* res=NULL; 
	FILE* file = fopen(nomFich,"r");
	if(!file){//vérification de la bonne ouverture du fichier
		printf("erreur de lecture du fichier\n");
		return NULL;
	}
	char *chaine;
	CellKey *c;
	while(fgets(ligne,256,file)!=NULL){

		tmp = str_to_key(ligne);
		chaine=key_to_str(tmp);
		printf("%s \n",chaine);
		ajout_en_tete_ckey(&res,create_cell_key(tmp));
		free(chaine);
		}
	fclose(file);	
	return res;
}


//5.3
void delete_cell_key(CellKey *key){
    free(key->data);
    free(key);
}

//5.3
//libère l'espace mémoire d'une liste chainée 
void delete_liste_key(CellKey *lc){
    CellKey *tmp = NULL; 
    while(lc){ 
        tmp = lc->next;
        delete_cell_key(lc);
        lc = tmp;
    }
    free(lc);
}


//5.4
//affichage dans le terminal d'une liste chainée de clés
void print_list_keys(CellKey* LCK){
	CellKey* tmp = LCK;
	char*tmpc= NULL;
	while(tmp){	
		tmpc = key_to_str(tmp->data);
		printf("%s\n",tmpc);
		free(tmpc);	
		tmp=tmp->next;
	}	
}

