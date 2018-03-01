#include "Catalogo_Artigos.h"
#include <stdlib.h>
#include <string.h> 

#define FIRST_DIGIT 10

struct artigo{
	char* title;
	long max_b;
	long max_w;
	CAT_R revisoes;
};

struct catalogo_a{
	AVL cat_artigos[FIRST_DIGIT];
	int all_r;
};

//Funcao para dar update ao titulo
static Artigo updateArtigo_T(Artigo a, char* n_t);
//Funcao para dar update ao num de bytes
static Artigo updateArtigo_MB(Artigo a, long n_max_b);
//Funcao para dar update ao num de palavras
static Artigo updateArtigo_MW(Artigo a, long n_max_w);
//Funcao para dar free do artigo, usada nas AVLs


// INIT's

Artigo initArtigo(){
	Artigo a = malloc(sizeof(struct artigo));
	a->title = NULL;
	a->max_b = 0;
	a->max_w = 0;
	a->revisoes = NULL;
	return a;
}

CAT_A initCatArtigos(){
	long i;
	CAT_A cat = malloc(sizeof(struct catalogo_a));
	for(i=0;i<FIRST_DIGIT;i++){
		cat->cat_artigos[i] = initAVL();
	}
	cat->all_r = 0;
	return cat;
}

// CREATE AND INSERT

Artigo newArtigo(char* t, int b, int w, CAT_R r){
	Artigo a = initArtigo();

	a->title = strdup(t);
	a->max_b = b;
	a->max_w = w;
	a->revisoes = r;

	return a;
}

CAT_A insertArtigo(CAT_A cat_a, long key, Artigo a){
	long i = get_first_digit(key);
	
	cat_a->cat_artigos[i] = insertAVL(cat_a->cat_artigos[i],key,a);
	return cat_a;
}

Artigo addRevisao(Artigo a, Revisao rev, long r_id){
	AVL r = insertRevisao(a->revisoes,r_id,rev);
	a->revisoes = r;
	return a;
}

// LOOKUP

Boolean lookUpArtigo(CAT_A cat, long key){
	long i = get_first_digit(key);
	if(cat->cat_artigos[i]==NULL) return false;
	return lookUpAVL(cat->cat_artigos[i],key);
}

// UPDATE DA INFO DE UM ARTIGO

Artigo update_A(Artigo a, char* t, long b, long w){
	if (strcmp(a->title,t) != 0) (updateArtigo_T(a,t));
	if (a->max_b < b) (updateArtigo_MB(a,b));
	if (a->max_w < w) (updateArtigo_MW(a,w));

	return a;
}

static Artigo updateArtigo_T(Artigo a, char* n_t){
	free(a->title);
	a->title = strdup(n_t);
	return a;
}

static Artigo updateArtigo_MB(Artigo a, long n_max_b){
	a->max_b = n_max_b;
	return a;
}

static Artigo updateArtigo_MW(Artigo a, long n_max_w){
	a->max_w = n_max_w;
	return a;
}

CAT_A updateCAT_A(CAT_A cat, Artigo a, long key){
	long i = get_first_digit(key);
	updateAVL(cat->cat_artigos[i],a,key);
	return cat;
}



// ADD

Boolean existeRevisao(CAT_R r, long key){
	if (r==NULL) return false;
	else return lookUpRevisao(r,key);
}

void artigoDuplicado(CAT_A cat,long key){
	long i = get_first_digit(key);
	addDuplicado(cat->cat_artigos[i]);
}

void incAllCAT_A(CAT_A cat){
	cat->all_r++;
}

// GET's


int getTamCatArtigos(CAT_A cat){
	int i, c=0;
	for (i=0;i<FIRST_DIGIT;i++){
		c+= getSizeAVL(cat->cat_artigos[i]);	
	}
	return c;
}

int getDuplicatesCAT_A(CAT_A cat){
	int i, c=0;
	for (i=0;i<FIRST_DIGIT;i++){
		c += getDuplicatesAVL(cat->cat_artigos[i]);
	}

	return c;
}

int getAllCAT_A(CAT_A cat){
	return cat->all_r;
}

char* getTitle(Artigo a){
	if(a){
		if(!(a->title)) return NULL;
		else{
		char* clone = strdup(a->title);
		return clone;
		}
	}

	return NULL;
}

long getMaxB(Artigo a){
	if(a) return a->max_b;
}

long getMaxW(Artigo a){
	if(a) return a->max_w;
}

AVL getCatalogo(CAT_A cat,int i){
	AVL clone = initAVL();
	clone = cat->cat_artigos[i];
	return clone;
}


Artigo getArtigo(CAT_A cat, long key){
	long i = get_first_digit(key);
	void* clone;

	clone = getEstruturaAVL(cat->cat_artigos[i],key);
	return clone;
}

CAT_R getArtigoRevisoes(Artigo a){
	if(a){ CAT_R r = a->revisoes;
		   return r;
	}

	return NULL;
}

// FREE's


void freeArtigo(Artigo a){
	 if(a){
	 free(a->title);
	 freeAVL(a->revisoes,(Funcao)freeRevisao);
	}
	free(a);
}

void freeCatArtigos(CAT_A cat){
	long i;
	for(i=0;i<FIRST_DIGIT;i++){
	freeAVL(cat->cat_artigos[i],(Funcao) freeArtigo);
	}
	free(cat);
}