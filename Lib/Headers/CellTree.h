#ifndef CELLTREE_H
#define CELLTREE_H

#include "Block.h"
typedef struct block_tree_cell {
 Block * block ;
 struct block_tree_cell * father ;
 struct block_tree_cell * firstChild ;
 struct block_tree_cell * nextBro ;
 int height ;
} CellTree ;

CellTree* create_node(Block* b);
int compare_node(CellTree* Node1, CellTree* Node2);
int update_height(CellTree* father, CellTree* child);
void add_child(CellTree* father, CellTree* child);
void print_tree(CellTree* cell);
void delete_node(CellTree* node);
void delete_tree(CellTree* root);
CellTree* last_node(CellTree* tree);
CellProtected *longest_chain_protected(CellTree *tree);
#endif 
