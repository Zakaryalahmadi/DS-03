#include <stdlib.h>
#include <stdio.h>
#include "key.h"
#include "cellKey.h"
#include "cellProtected.h"

#ifndef HASHTAB_H
#define HASHTAB_H

typedef struct hashcell{
	Key* key;
	int val;
} HashCell;

typedef struct hashtable{
	HashCell** tab;
	int size;
} HashTable;

HashCell* create_hashcell(Key* key);
void delete_hashcell(HashCell* hcell);
int hash_function(Key* key,int size);
int find_position(HashTable* t, Key* key);
HashTable* create_hashtable(CellKey* keys, int size);

 void delete_hashtable(HashTable* htab);

Key* compute_winner(CellProtected* decl, CellKey* candidates,CellKey* voters, int sizeC, int sizeV);

#endif 
