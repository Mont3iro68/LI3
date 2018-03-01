#ifndef _CATALOGO_CONTRIBUIDORES_H_
#define _CATALOGO_CONTRIBUIDORES_H_

#include "avl.h"
#include "utility.h"

typedef struct contribuidor* Contribuidor;
typedef struct catalogo_c* CAT_C;

//Funcao que inicia uma estrutura Contribuidor(username,ncontribuiçoes)
Contribuidor initContribuidor();

//Funcao que inicia a estrutura de Catalogo de AVLs para os contribuidores
CAT_C initCatContribuidores();

//Funcao para criar um novo contribuidoe atribuindo-lhe o username
Contribuidor newContribuidor(char* u);

//Funcao para inserir um contribuidor no Catalogo de contribuidores
CAT_C insertContribuidor(CAT_C cat, Contribuidor c, long key);

//Funcao para dar update no Catalogo (atualiza a estrutura do contribuidor)
CAT_C updateCAT_C(CAT_C cat, Contribuidor c, long key);

//Funcao utilizada para procurar por um contribuidor no seu Catalogo
Boolean lookUpContribuidor(CAT_C cat, long key);

//Get do username do contribuidor
char* getUsername(Contribuidor c);

//Get do numero total de contribuiçoes do contribuidor
int getTotalRevisions(Contribuidor c);

//Funçao para incrementar o numero de contribuiçoes de um contribuidor
Contribuidor addContribuicao(Contribuidor c);

//Get da estrutura de um contribuidor, no catalogo de conttibuidores 
Contribuidor getContribuidor(CAT_C cat, long key);

void freeContribuidor(Contribuidor c);
void freeCatContribuidores(CAT_C cat);

#endif