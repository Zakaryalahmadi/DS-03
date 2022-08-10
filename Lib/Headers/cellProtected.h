#ifndef cellProtected_h
#define cellPotected_h
#include "Protected.h"

typedef struct cellProtected{
	Protected* data;
	struct cellProtected* next;
} CellProtected;

CellProtected* create_cell_protected(Protected* pr);
int compteCellProtected(CellProtected* cell);
void ajout_en_tete_cpr(CellProtected **lc, CellProtected *pr);
CellProtected* read_protected(char* nomFich);
void print_list_pr(CellProtected* LCP);
void delete_cell_pr(CellProtected *pr);
void delete_liste_pr(CellProtected *lc);
void verif_fraud(CellProtected ** lc);
int len_cellprotected(CellProtected* c);
void fusion_cell_pr(CellProtected** debut, CellProtected ** fin);

#endif
