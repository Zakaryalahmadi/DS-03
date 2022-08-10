#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/signature.h"
#include "Headers/key.h"
#include "Headers/src.h"

//3.6
//alloue et remplie une signature en mémoire
Signature* init_signature(long* content, int size){
    Signature *s = (Signature*) malloc(sizeof(Signature));

	if(s == NULL){
		printf("Erreur d allocation");
		return NULL;
	}
	s->mess = content;
	s->taille = size;

	return s;

	
}
//3.7
//alloue et remplie une signature à partir d'un message mess
Signature* sign(char* mess, Key* sKey){
	return init_signature(encrypt(mess,sKey->val, sKey->n), strlen(mess));
}

//3.8
//fonctions fournies
char *signature_to_str(Signature *sgn){ 
    char * result = (char*) malloc(10 * sgn->taille * sizeof(char));
    if(!result){    
        printf("Erreur d'allocation\n");
        free(result);
        return NULL;
    }

    result[0] = '#' ;
    int pos = 1;
    char buffer[156];
    for(int i = 0; i < sgn->taille; i++){
        sprintf(buffer ,"%lx" , sgn->mess[i]);
        for(int j = 0; j < strlen(buffer) ; j++){
            result[pos] = buffer[j];
            pos++;
        }
        result[pos] = '#' ;
        pos=pos+1;
    }
    result[pos] = '\0' ;
    result = realloc(result , (pos + 1) * sizeof(char)); 
    return result;
}

//fonction fournie
Signature *str_to_signature(char *str){ //fonction fourni
    int len = strlen(str);
    long *content = (long*)malloc(sizeof(long)*len); //allocation de mémoire
    if(!content){
        printf("Erreur d'allocation\n");
        free(content);
        return NULL;
    }
    int num = 0;
    char buffer [256];
    int pos = 0;
    for(int i=0; i<len ; i++){
        if (str[i] != '#'){
            buffer [pos] = str[i];
            pos = pos+1;
        }else{
            if(pos != 0){
                buffer[pos] = '\0';
                sscanf(buffer , "%lx" , &(content[num])) ;
                num = num + 1;
                pos = 0;
            }
        }
    }
    content = realloc(content , num*sizeof(long)); //allocation de mémoire
    return init_signature(content , num); //allocation de mémoire
}

//libère une signature en mémoire
void delete_signature(Signature *sign){
    
    free(sign->mess);
    free(sign);
}
