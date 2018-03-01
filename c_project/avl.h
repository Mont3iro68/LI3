#ifndef _AVL_H_
#define _AVL_H_

#include "utility.h"

typedef struct avl* AVL;
typedef struct nodo* NODO;
typedef void* Estrutura;
typedef void(*Funcao)(void*);

//Inicia uma nova AVL
AVL initAVL();

NODO initNODO();

//Insere na AVL um nodo tendo como referência um long id;
AVL insertAVL(AVL novo, long id, void *estrutura);

//Devolve um Boolean caso encontre na AVL o long id;
Boolean lookUpAVL(AVL t, long id);

//Update de uma estrutura dentro de uma AVL;
AVL updateAVL(AVL t, Estrutura e, long key);

//Executa o clone de uma AVL;
AVL cloneAVL(AVL n, AVL novo);

//Devolve o tamanho de uma AVL;
int getSizeAVL(AVL t);

//Devolve os duplicados de uma AVL;
int getDuplicatesAVL(AVL t);

//Dado um Nodo retorna a copia do seu long;
long getValorAVL(AVL t, long key);

NODO getNodoDIR(NODO n);

NODO getNodoESQ(NODO n);
//incrementa o valor de duplicados da AVL
void addDuplicado(AVL t);

//Devolve a estrutura associada a uma nodo de uma AVL atraves de um long
Estrutura getEstruturaAVL (AVL n, long id);

//Devolve a estrutura dado um NODO
Estrutura getEstrutura(NODO n);

NODO getHead(AVL t);

long getValorNODO(NODO n);
//Devolve o clone de uma AVL
AVL cloneAVL(AVL n, AVL novo);
 
//Fuñção com o objetivo de limpar uma AVL;
void freeAVL(AVL n, Funcao f);

#endif