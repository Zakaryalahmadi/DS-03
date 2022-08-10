#ifndef src_h
#define src_h


int tablen (long* tab);
void print_long_vector (long* result, int size);
int is_prime_naive(long p);
long modpow_naive(long a, long m,long n);
long modpow(long a, long m, long n);
void creerfichier(long a,long m,long n);
int witness ( long a , long b , long d , long p ) ;
long rand_long(long low , long up) ;
int is_prime_miller ( long p , int k );
int puissance(long a,long m);
long random_prime_number(int low_size, int up_size, int k);
long extended_gcd ( long s , long t , long *u , long * v );
long *encrypt(char* chaine, long s, long n);
char* decrypt(long* crypted, int size, long u, long n);
int intComparator ( const void * first, const void * second );
int is_in_tab(int* tab, int taille, int n);
void mem_reset(char *buff, size_t n);



#endif

