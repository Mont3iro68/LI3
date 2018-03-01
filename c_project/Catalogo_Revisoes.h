#ifndef __CATALOGO_REVISOES_H__
#define __CATALOGO_REVISOES_H__

#include "avl.h"
#include "utility.h"

typedef struct revisao* Revisao;
typedef AVL CAT_R;

Revisao initRevisao();
CAT_R initCatRevisao();
Revisao newRevisao(char* tstamp);
CAT_R insertRevisao(CAT_R cat, long key, Revisao r);
Boolean lookUpRevisao(CAT_R cat, long key);
CAT_R updateDuplicates_R(CAT_R cat,long key);
int countRevisions(CAT_R cat);
char* getTimestamp(Revisao r);
char* getTAG(Revisao r);
Revisao getRevisao(CAT_R cat, long key);
void freeRevisao(Revisao r);
void freeCatRevisoes(CAT_R cat);


#endif