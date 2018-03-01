#include "Catalogo_Contribuidores.h"
#include <stdlib.h>
#include <string.h> 

#define FIRST_DIGIT 10

// elem count e get estrutura

struct contribuidor{
	char* username;
	int total_revisions;
};
	
struct catalogo_c{
	AVL cat_contribuidores[FIRST_DIGIT];
};


// INIT's

Contribuidor initContribuidor(){
	Contribuidor c = malloc(sizeof(struct contribuidor));
	c->username = NULL;
	c->total_revisions = 0;
	return c;
}

CAT_C initCatContribuidores(){
	long i;
	CAT_C cat = malloc(sizeof(struct catalogo_c));
	for(i=0;i<FIRST_DIGIT;i++){
		cat->cat_contribuidores[i] = initAVL();
	}
	return cat;
}

// CREATE AND INSERT

Contribuidor newContribuidor(char* u){
	Contribuidor c = initContribuidor();
	c->username = strdup(u);
	c->total_revisions = 1;
	return c;
}

CAT_C insertContribuidor(CAT_C cat, Contribuidor c, long key){
	long i = get_first_digit(key);
	cat->cat_contribuidores[i] = insertAVL(cat->cat_contribuidores[i],key,c);
	return cat;
}

CAT_C updateCAT_C(CAT_C cat, Contribuidor c, long key){
	long i = get_first_digit(key);
	updateAVL(cat->cat_contribuidores[i],c,key);
	return cat;
}

// LOOKUP

Boolean lookUpContribuidor(CAT_C cat, long key){
	long i = get_first_digit(key);
	if(cat->cat_contribuidores[i]==NULL) return false;
	return lookUpAVL(cat->cat_contribuidores[i],key);
}

// GET's

char* getUsername(Contribuidor c){
	if(!c->username) return NULL;
	else{
		char* clone = strdup(c->username);
		return clone;
	}
}

int getTotalRevisions(Contribuidor c){
	return c->total_revisions;
}

Contribuidor addContribuicao(Contribuidor c){
	if(c) c->total_revisions++;
	return c;
}

Contribuidor getContribuidor(CAT_C cat, long key){
	long i = get_first_digit(key);
	void* clone;

	clone = getEstruturaAVL(cat->cat_contribuidores[i],key);
	return clone;
}


// FREE's
void freeContribuidor(Contribuidor c){
	if (c){
	free(c->username);
	free(c);
	}
}

void freeCatContribuidores(CAT_C cat){
	long i;

	for(i=0;i<FIRST_DIGIT;i++){
		 freeAVL(cat->cat_contribuidores[i],(Funcao)freeContribuidor);
	}
	free(cat);
}