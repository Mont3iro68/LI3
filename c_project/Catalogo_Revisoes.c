#include "Catalogo_Revisoes.h"
#include <stdlib.h>
#include <string.h>

static Boolean lookUpRevisao_AUX(NODO n, long key, char* t_key);

struct revisao{
	char* timestamp;
};

// INIT's

Revisao initRevisao(){
	Revisao r = malloc(sizeof(struct revisao));
	r->timestamp = NULL;
	return r;
}

CAT_R initCatRevisao(){
	CAT_R cat = initAVL();
	return cat;
}

//CREATE AND INSERT

Revisao newRevisao(char* tstamp){
	Revisao r = initRevisao();
	r->timestamp = strdup(tstamp);
	return r;
}

CAT_R insertRevisao(AVL t,long key,Revisao r){
	t = insertAVL(t,key,r);
	return t;
}

// LOOKUP

Boolean lookUpRevisao(CAT_R cat, long key){
	if(cat==NULL) return false;
	else lookUpAVL(cat,key);
}

// UPDATE

CAT_R updateDuplicates_R(CAT_R cat,long key){
	addDuplicado(cat);
	return cat;
}

// COUNT

int countRevisions(CAT_R cat){
	int total = 0;
	total += getSizeAVL(cat);
	total += getDuplicatesAVL(cat);
	return total;
}

// GET's

char* getTimestamp(Revisao r){
	if(r){ char* clone = strdup(r->timestamp);
		   return clone;
	}
}



Revisao getRevisao(CAT_R cat, long key){
	void* clone;
	clone = getEstruturaAVL(cat,key);
	return clone;
}

// FREE's

void freeRevisao(Revisao r){
	if (r){
	free(r->timestamp);
	free(r);
	}
}

void freeCatRevisoes(CAT_R cat){
	freeAVL(cat,(Funcao)freeRevisao);
}
