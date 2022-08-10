 #include <stdio.h>
 #include <stdlib.h>
 #include "Headers/cellProtected.h"
 #include "Headers/Protected.h"
 
 //5.6
CellProtected* create_cell_protected(Protected* pr){
	CellProtected* res = calloc(1,sizeof(CellProtected));
	if(!res){
		printf("erreur d'allocation");
		return NULL;
	}
	res->data=pr;
	res->next=NULL;
	return res;
}

//5.7
//ajoute un chainon de déclaration en tête d'une liste chainée
void ajout_en_tete_cpr(CellProtected **lc, CellProtected *pr){
	if(!lc){
		*lc = pr;
		return;
	}
	pr->next =*lc;
	*lc=pr;
} 

//5.8
//transforme un fichier formaté en une liste chainée de déclaration 
CellProtected* read_protected(char* nomFich){
	char ligne[256];
	Protected *tmp = NULL;
	CellProtected* res=NULL;
	FILE* file = fopen(nomFich,"r");

    //vérification de la bonne ouverture du fichier
	if(!file){
		printf("erreur de lecture du fichier\n");
		return NULL;
	}
	while(fgets(ligne,256,file)!=NULL){
        tmp = str_to_protected(ligne);
        ajout_en_tete_cpr(&res,create_cell_protected(tmp));
    }
	fclose(file);	
	return res;
}

//5.9
//affiche une liste chainée de déclarations
void print_list_pr(CellProtected* LCP){
	CellProtected* tmp = LCP;
    char* chaine=NULL;
    int i=0;
	while(tmp){
        chaine=protected_to_str(tmp->data);
        free(chaine);
		tmp=tmp->next;
	}
	
}
//5.10
//libère un chainon de type CellProtected
void delete_cell_protected(CellProtected *pr){
    delete_protected(pr->data);
    free(pr);
}

//5.10
//libère l'intégralité d'une liste chainée
void delete_liste_protected(CellProtected *lc){
    CellProtected *tmp = NULL; 
    while(lc){ 
        tmp = lc->next;
        delete_cell_protected(lc);
        lc = tmp;
    }
    free(lc);
}

//6.1 
//vérifie que chaque chainon contient une déclaration valide, la supprime sinon
void verif_fraud(CellProtected ** cp){
	CellProtected* prec = *cp;
    
    if (!prec->data || !verify(prec->data)){
        *cp = (*cp)->next;
        delete_cell_pr(prec);
    }
    
    prec = *cp;
    CellProtected* tmp = (*cp)->next;

    while (tmp){
        if (!tmp->data || !verify(tmp->data)){
            if (!tmp->next){
                delete_cell_pr(tmp);
                prec->next = NULL;
            }
            else{
                prec->next = tmp->next;
                delete_cell_pr(tmp);
            }
        }
        prec = prec->next;
        tmp = tmp->next;
    }
}


int len_cellprotected(CellProtected* c){
    int count = 0;
    CellProtected* tmp=c;
    while(tmp){
        count++;
        tmp=tmp->next;
    }

    return count;
}

//8.8

void fusion_cell_pr(CellProtected** debut, CellProtected ** fin){
	if(!*debut){
        *debut=*fin;
        *fin=NULL;
        return;
    }
    CellProtected* tmp = *debut;
	while(tmp->next){
        tmp=tmp->next;
    }
	tmp->next = *fin;
    *fin=NULL;
}
	
	
	
	

