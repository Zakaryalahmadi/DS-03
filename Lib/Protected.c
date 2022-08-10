#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Headers/signature.h"
#include "Headers/Protected.h"
#include "Headers/signature.h"
#include "Headers/src.h"

//3.10
//alloue et initialise un protected avec tout les éléments nécéssaire 
Protected* init_protected(Key* pKey, char* mess, Signature* sgn){
    Protected *p = (Protected*)malloc(sizeof(Protected));
    if(p == NULL){
        printf("Erreur d allocation");

        return NULL;
    }
    p->k=pKey;
    p->mess=strdup(mess);
    p->s=sgn;
    return p;
}
// fonction maison pour libérer l'espace mémoire d'un protected
void delete_protected(Protected *p){
    free(p->k);
    free(p->mess);
    delete_signature(p->s);
    free(p);
}

//3.11
//verifie que la signature correspond bien à la personne et au message 
int verify(Protected* pr){
    char* tmp =decrypt(pr->s->mess, pr->s->taille, pr->k->val, pr->k->n);
    int res = (strcmp(tmp,pr->mess)==0);
    free(tmp);
    return res;
}

//3.12
//transforme un portected en string pour stocker dans un fichier
char* protected_to_str(Protected* P)
{
    char* ptos = (char*) malloc(256 * sizeof(char));
    if(ptos == NULL){
        printf("Erreur d allocation (protected_to_str)\n");
        return NULL;
    }

    char* temp = signature_to_str(P->s);
    char* temp2 = key_to_str(P->k);
    sprintf(ptos, "%s , %s , %s", temp2, P->mess, temp);
    free(temp);
    free(temp2);
    return ptos;
}

//3.12
//transforme une chaine de caractère formatée en protected pour extraire d'un fichier texte
Protected*  str_to_protected(char* protected){
    char* strkey = (char*)malloc(sizeof(char)*256);
    if(strkey == NULL){
        printf("Erreur d allocation");

        return NULL;
    }
    char *strmess = (char*)malloc(sizeof(char)*256);
    if(strmess == NULL){
        printf("Erreur d allocation");

        return NULL;
    }
    char*strsignature = (char*)malloc(sizeof(char)*256);
    if(strsignature == NULL){
        printf("Erreur d allocation");

        return NULL;
    }

    sscanf(protected, "%s , %s , %s",strkey,strmess,strsignature);
    Protected* res = init_protected(str_to_key(strkey),strmess,str_to_signature(strsignature));
    free(strkey);
    free(strmess);
    free(strsignature); 

    return res;
    
    
} 
//4.1
//generation de données aléatoires pour tester nos fonctions
void generate_random_data (int nv, int nc){
//creation de fichiers 
    FILE* keytxt = fopen("keys.txt", "w+");
    FILE* candidattxt = fopen("candidates.txt", "w+");
    FILE* declarationtxt = fopen("declarations.txt", "w+");

    //Partie cles 
    Key* pKey = (Key *) malloc(sizeof(Key));
    Key* sKey = (Key *) malloc(sizeof(Key));

    for (int i = 0; i < nv; i++){

        init_pair_keys(pKey, sKey, 3, 7); 
        //on initialise la paire de cle
        fprintf(keytxt, "(%lx,%lx) (%lx,%lx)\n", pKey->val, pKey->n, sKey->val, sKey->n);
    }
    free(pKey);
    free(sKey);

    //Partie candidat 
    char ligne[256] = {0};
    char* buff = ligne;
    size_t len = sizeof(ligne);
    int candidates[nc]; 
    //tableau contenant les indices de ligne des candidats
    
    int i,num; 
    i=0;
    while (i < nc){  
        num = (int) ((rand() % nv) + 1);           
        if (is_in_tab(candidates, i, num) == 0){
            candidates[i] = num;
            i++;
        }
    }

    
    
    qsort(candidates, nc, sizeof(int), intComparator);
    //on trie les candidats afin de faire un seul passage
    
    int n = 0;
    rewind(keytxt);
    for (i = 0; i < nc; i++){
        while (n != candidates[i]){
            fgets(buff, 256, keytxt);   
            n++;                    
        }
        fputs(buff, candidattxt);                   
    }
    mem_reset(buff, len); 


    rewind(keytxt);         
    char public[256];
    char secret[256];
    n = 0;

    //declaration des variables
    Key* kpublic;
    Key* ksecret;
    Signature* s;
    char* mess;

    //buffer pour le second fichier au cas où il est possible de perdre la progression sur le premier fichier
    char line[256] = {0};
    char* buffer = line;
    size_t length = sizeof(ligne);

    //parcours du fichier des clés
    for (i = 1; i < nv + 1; i++){
        fgets(buff, 256, keytxt);
        sscanf(buff, "%s %s", public, secret);
        kpublic = str_to_key(public);
        ksecret = str_to_key(secret);
            
        if (is_in_tab(candidates, nc, i) == 0){                                           
            num = (int) ((rand() % nc) + 1);
           
            while (n != num){
                fgets(buffer, 256, candidattxt); 
                n++;                    
            }
            
            sscanf(buffer, "%s %s", public, secret);
        }
        s = sign(public, ksecret);                  
        //on effectue la déclaration de vote en chiffrant la clé publique du candidat 
        
        Protected* pr = init_protected(kpublic, public, s);
        mess = protected_to_str(pr);
        fprintf(declarationtxt, "%s\n", mess);                  
        //avant de tout print dans le fichier declarations.txt

        delete_protected(pr);
        free(mess);
        free(ksecret);
        
        rewind(candidattxt);          
        //rewind du fichier candidat  
        n = 0;               
        //pour le prochain électeur
    }
    mem_reset(buff, len);        
    //reset de la mémoire au cas où
    mem_reset(buffer,length);

    fclose(keytxt);
    fclose(candidattxt);
    fclose(declarationtxt);
}
