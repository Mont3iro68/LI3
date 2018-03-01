#ifndef _parser_h_
#define _parser_h_

#include "Catalogo_Artigos.h"
#include "Catalogo_Contribuidores.h"
#include "Catalogo_Revisoes.h"
#include "avl.h"
#include "utility.h"


/*Função que ao percorrer os snapshots filtra a informação do xml e 
insere-a nas estrutura, atraves da funçao insere */
void parseDoc(char *docname, CAT_A artigos, CAT_C contribuidores);

#endif