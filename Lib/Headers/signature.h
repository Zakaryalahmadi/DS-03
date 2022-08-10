#ifndef signature_h
#define signature_h
#include "key.h"


typedef struct signature{
	long *mess;
	int taille;
}Signature;

Signature* init_signature(long* content, int size);
Signature* sign(char* mess, Key* sKey);
Signature *str_to_signature(char *str);
char *signature_to_str(Signature *sgn);
void delete_signature(Signature *sign);



#endif
