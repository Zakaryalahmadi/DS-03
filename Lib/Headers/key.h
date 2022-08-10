#ifndef KEY_H
#define KEY_H

typedef struct key{
	long val;
	long n;
}Key;

void generate_key_values(long p,long q, long* n, long*s, long *u);
void init_key(Key* key, long val, long n);
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size);
char* key_to_str(Key* key);
Key* str_to_key(char* str);
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size);
Key *create_key();



#endif
