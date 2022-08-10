#ifndef BLOCK_H
#define BLOCK_H
#include "hashtab.h"

typedef struct block {
	Key * author ;
	CellProtected * votes ;
	unsigned char * hash ;
	unsigned char * previous_hash ;
	int nonce ;	
 } Block ;

 void write_block(char* nom,Block *b);
 Block* file_to_block(char* Nom);
 char* block_to_str(Block* block);
 unsigned char* str_to_SHA256(char* str);
 void compute_proof_of_work(Block *B, int d);
 int verify_block(Block* b, int d);
 void creerfichierblock(Block *B,int d);
 void delete_block(Block*b);

#endif 
