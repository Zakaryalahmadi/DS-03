 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "Headers/Votes.h"
 #include "Headers/Block.h"
 # include <dirent.h>


//9.1
void submit_vote(Protected*p){

	FILE* fp=fopen("Pending_votes.txt","a");
  char* chaine=protected_to_str(p);
	fprintf(fp,"%s\n",chaine);
  free(chaine);
  fclose(fp);
  
}
//9.2

void  create_block(CellTree* tree,Key* author,int d){
    Block *b=(Block*)malloc(sizeof(Block));
    if(b==NULL) printf("Erreur d'allocation");
    b->hash=NULL;
    Key *k = create_key();
    init_key(k, author->val, author->n);
    b->author = k;

    CellProtected *pr = read_protected("Pending_votes.txt");
    b->votes=pr;
    if (tree){
    CellTree *lN = last_node(tree);
    b->previous_hash =strdup((lN->block)->hash);
  }
  else{
      b->previous_hash=NULL;
  }
    compute_proof_of_work(b,d);
    remove("Pending_votes.txt");
     
    write_block("Pending_block.txt", b);
    
    delete_block(b);

}

//9.3

void add_block(int d, char* name){
    
    Block *b =file_to_block("Pending_block.txt");

    if(verify_block(b,d)){
      char str[256];
      strcpy(str, "Blockchain/");
      
      strcat(str, name);
    
      write_block(str, b);
    
    }
    
    delete_block(b);
    remove("Pending_block.txt");


}

//9.4

CellTree* read_tree(){
    DIR *rep = opendir("Blockchain");
    int size=0;
   if(rep!=NULL){
    struct dirent *dir ;
      while (( dir = readdir(rep) ) ) {
          if ( strcmp ( dir->d_name , "." ) !=0 && strcmp( dir->d_name , "..") !=0) {
              if((strcmp(dir->d_name, "Pending_block.txt") != 0) && (strcmp(dir->d_name, "Pending_votes.txt") != 0)){
                size++;
              }  
          }
      }
    
    rewinddir(rep);
    CellTree** tab=(CellTree**)(calloc(size,sizeof(CellTree*)));

    if(tab==NULL) printf("Erreur d'allocation \n");

    Block *b;
    CellTree *t;
    int i= 0;
    char tmp[256];  

 
    while (dir = readdir(rep)) {
      if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..")) && (strcmp(dir->d_name, ".gitkeep") != 0)) {
        if ((strcmp(dir->d_name, "Pending_block.txt") != 0) && (strcmp(dir->d_name, "Pending_votes.txt") != 0)) {
          strcpy(tmp, "Blockchain/");
          strcat(tmp, dir->d_name);
          
          b = file_to_block(tmp);
          t = create_node(b);
          tab[i++] = t;
        }
      }
    }


    for (int i = 0; i < size; i++){
        for(int j = 0; j<size; j++){
            if( ((tab[j]->block)->previous_hash!=NULL) && (strcmp((tab[i]->block)->hash,(tab[j]->block)->previous_hash)==0))
            add_child(tab[i],tab[j]);
        }
    }

    CellTree* res;
    for (int i = 0; i < size; i++){
        if((tab[i]->father)==NULL)
            res=tab[i];
    }
    
    free(tab);
    closedir(rep);

    return res;
   }
}


//9.5

Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV) {
  CellProtected *CP = longest_chain_protected(tree);
  fraudverif(&CP);
  Key *res = compute_winner(CP, candidates, voters, sizeC+10, sizeV+10);
  delete_liste_pr(CP);

  return res;
}
