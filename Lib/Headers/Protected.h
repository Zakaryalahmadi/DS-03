#ifndef protected_h
#define protected_h
#include "key.h"
#include "signature.h"
typedef struct protected{
    Key *k;
    Signature *s;
    char* mess; 
} Protected;

Protected* init_protected(Key* pKey, char* mess, Signature* sgn);
void delete_protected(Protected *p);
int verify(Protected* pr);
char* protected_to_str(Protected *pr);
Protected*  str_to_protected(char* protected);
void generate_random_data (int nv, int nc);

#endif
