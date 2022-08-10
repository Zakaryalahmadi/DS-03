#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Headers/CellTree.h"


//8.1
//Crée et alloue un nœud d'un arbre
CellTree* create_node(Block* b){

    CellTree *node = (CellTree*)calloc(1,sizeof(CellTree));
    if(node==NULL)
    {
        printf("Erreur d'allocation");
    }
    node->block=b;
    node->father=NULL;
    node->firstChild=NULL;
    node->nextBro=NULL;
    node->height=0; 

    return node;

}

//8.2
//mets à jour la hauteur d'un père après modification du fils
int update_height(CellTree* father, CellTree* child){
    int res = father->height;
    int test;
    CellTree* tmp= child;     
    while(tmp){
        test = tmp->height;
        if (tmp->height >= res){
            father->height = test+1;
            return 1;
        }   
        tmp = tmp->nextBro;
    }
    return 0;
}

//8.3
//fonction permettant d'ajouter un enfant à un block et de mettre à jour la hateur de tous ses ascendants
void add_child(CellTree* father, CellTree* child){
    child->nextBro = father->firstChild;
    father->firstChild = child;
    child->father = father;
    int test;
    if(update_height(father,child)){ // si nous avons 
        CellTree* tmp = father->father;
        CellTree* prec = father;
        while(tmp){
            test = update_height(tmp, prec);
            prec = tmp;
            tmp = tmp->father;
            if(!test){return;}        
        }
    }
}

//8.4
//affiche un arbre de block avec pour chaque noeud sa hauteur et sa valeure hachée

void print_tree(CellTree* cell){
    if(!cell){return;}
    printf("---------------------------------------------\n");
    printf("h = %d\n",cell->height);
    printf("hash val = %s \n", cell->block->hash);
    print_tree(cell->nextBro);
    print_tree(cell->firstChild);
}

//8.5
//fonction pour libérer une node de l'arbre
void delete_node(CellTree* node){
    if(!node){return;}
    delete_block(node->block);
    
    free(node);
}

//8.5
//fonction pour libérer un arbre
void delete_tree(CellTree* root){
    if(!root){return;}
    delete_tree(root->nextBro);
    delete_tree(root->firstChild);
    delete_node(root);
}
//8.6
//renvoie le fils avec la plus grande hauteur de cell
CellTree* highest_child(CellTree* cell){
	if(!cell){return NULL;}
    if(!cell->firstChild){return NULL;}
	CellTree* tmp = cell->firstChild;
	CellTree* res = cell->firstChild;
	int height = tmp->height;
	while(tmp){
		if (tmp->height > height){
			height = tmp->height;
			res=tmp;
		}
		tmp=tmp->nextBro;
	}
	
	return res;
}
	
//8.7
//renvoie le nœud le plus profond de l'arbre tree
CellTree* last_node(CellTree* tree){
	if(!tree){return NULL;}
	CellTree* res = tree;
	while(res->firstChild){
		res = highest_child(res);
	}
	return res;
}


//(8.8 voir le fichier CellProtected.c)
		

//8.9
//renvoie la liste chainées des déclarations de la plus longue chaine de l'arbre
CellProtected *longest_chain_protected(CellTree *tree) {
    
  if (tree == NULL) {return NULL;}
  CellProtected *list = NULL;
  CellProtected* tmp= (tree->block)->votes;
  for(int i=1;i<10;i++){
      tmp=tmp->next;
  }
  tmp=NULL;

 // print_list_pr(( tree->block)->votes);
  fusion_cell_pr(&list, &((tree->block)->votes));
   print_list_pr(list);
  CellTree *highestChild = highest_child(tree); 
  while (highestChild != NULL) {
    fusion_cell_pr(&list, &((highestChild->block)->votes));
    print_list_pr(list);
    print_list_pr(highestChild->block->votes);
    highestChild = highest_child(highestChild);
  }
  return list;
}
		
		
		
		
	
			









