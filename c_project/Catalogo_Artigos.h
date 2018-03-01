#ifndef _CATALOGO_ARTIGOS_H_
#define _CATALOGO_ARTIGOS_H_

#include "avl.h"
#include "Catalogo_Revisoes.h"
#include "utility.h"

typedef struct artigo* Artigo;
typedef struct catalogo_a* CAT_A;

//Inicia a estrutura de um artigo
Artigo initArtigo();

//Inicia a estrutura de Catalogo de AVLs para os artigos
CAT_A initCatArtigos();

//Cria um novo Artigo com o seu titulo tamanho em palavras e bytes e o avl de revisoes
Artigo newArtigo(char* t, int b, int w, CAT_R r);

//Insere um Artigo no catalogo de Artigos ordenando-os por id de artigo 
CAT_A insertArtigo(CAT_A cat_a, long key, Artigo a);

//Funçao usada para inserir uma revisao numa AVL de revisoes
Artigo addRevisao(Artigo a, Revisao r, long r_id);

//Funçao usada para procurar um Artigo no Catalogo 
Boolean lookUpArtigo(CAT_A cat, long key);

//Funcao utilizada para dar update ao artigo caso seja preciso
Artigo update_A(Artigo a, char* t, long b, long w);

//Da update a um artigo no catalogo dos Artigos
CAT_A updateCAT_A(CAT_A cat, Artigo a, long key);

//Get do tamanho do Catalogo (numero de Artigos nao repetidos)
int getTamCatArtigos(CAT_A cat);

//Get do numero de Artigos duplicados
int getDuplicatesCAT_A(CAT_A cat);

//Get do numero total de Artigos passados no parser
int getAllCAT_A(CAT_A cat);

//Get do titulo do Artigo 
char* getTitle(Artigo a);

//Get do numero maximo de Bytes das Revisoes do Artigo
long getMaxB(Artigo a);

//Get do numero maximo de Bytes das Revisoes do Artigo
long getMaxW(Artigo a);

AVL getCatalogo(CAT_A cat,int i);

//Funcao que incrementa sempre que chega um Artigo(c/repetidos)
void incAllCAT_A(CAT_A cat);

//Get do Artigo 
Artigo getArtigo(CAT_A cat, long key);

//Get da estrutura que guarda cada Revisao do artigo
CAT_R getArtigoRevisoes(Artigo a);

void free_Artigo(Artigo a);
void freeCatArtigos(CAT_A cat);
#endif