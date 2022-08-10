#ifndef cellKey_h
#define cellkey_h
#include "key.h"

typedef struct cellKey {
	Key * data;
	struct cellKey* next;
}CellKey;

CellKey* create_cell_key(Key* key);
void ajout_en_tete_ckey(CellKey** lc, CellKey* key);
CellKey* read_public_keys(char* nomFich);
void print_list_keys(CellKey* LCK);
void delete_cell_key(CellKey *key);
void delete_liste_key(CellKey *lc);

#endif 
