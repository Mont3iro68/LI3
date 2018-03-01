#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "./headers/Catalogo_Artigos.h"
#include "./headers/Catalogo_Contribuidores.h"
#include "./headers/Catalogo_Revisoes.h"
#include "./headers/avl.h"
#include "./headers/utility.h"




/*
ORDEM DO ARRAY
d[0] = article_title;
d[1] = article_id;
d[2] = revision_id;
d[3] = revision_word_count;
d[4] = revision_timestamp;
d[5] = contributor_username || contributor_ip;
d[6] = contributor_id;
d[7] = revision_text_size
*/


//Funçao responsavel por filtrar a informaçao relacionada com o artigo
static void parse_Article (char** data, xmlDocPtr doc, xmlNodePtr cur);
//Funçao responsavel por filtrar a informaçao relacionada com o contribuidor e revisao
static void parse_Revision (char** data, xmlDocPtr doc, xmlNodePtr cur);
//Funçao responsavel por inserir os dados lidos no parse_Article/parse_Revision
static void insere(char** d, CAT_A artigos, CAT_C contribuidores);

void parseDoc(char *docname, CAT_A artigos, CAT_C contribuidores){
	int i;
    char** data = malloc(8*sizeof(data)); //Array que vai recolher a informaçao de uma page
    xmlDocPtr doc;
    xmlNodePtr cur, aux;

    doc = xmlParseFile(docname);
    //Erro caso o documento nao seja valido
    if (doc==NULL){
        fprintf (stderr,"Erro! \n");
        return;
    }
    cur = xmlDocGetRootElement(doc);
    //Erro caso o documento esteja vazio/nao seja xml
    if (cur == NULL){
        fprintf(stderr, "Ficheiro vazio!");
        xmlFreeDoc(doc);
        return;
    }

    cur = cur->xmlChildrenNode;
    //Ciclo que vai, ao ler a informaçao, inseri-la nas estruturas
    while (cur != NULL){
        aux = cur;
        //Ao encontrar uma page (novo artigo), faz o parse da informaçao e insere-a.
        if (!xmlStrcmp(cur->name,(const xmlChar *)"page")){
        parse_Article(data,doc,cur); //Funçao parse
        insere(data,artigos,contribuidores); //Funçao insere
        cur = aux;
        }
        cur = cur->next; 
             
    }
    xmlFreeDoc(doc);
    free(data);
}


static void parse_Article (char** data, xmlDocPtr doc, xmlNodePtr cur){
    xmlChar* info;
    cur = cur->xmlChildrenNode;

    //ciclo para avançar no xml
    for(;cur;cur = cur->next){
        if((xmlStrcmp(cur->name, (const xmlChar*)"title")) == 0){ //ao encontrar o titulo
            info = xmlNodeListGetString(doc,cur->xmlChildrenNode,1); 
            data[0] = strdup(info); //copia a info do titulo para o devido indice no array 
            xmlFree(info);

        }
        
        else if((xmlStrcmp(cur->name, (const xmlChar*)"id")) == 0){//ao encontrar o id do Artigo
            info = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            data[1] = strdup(info);//copia a info do idArtigo para o devido indice no array 
            xmlFree(info);
        }
        
        	else if((xmlStrcmp(cur->name, (const xmlChar*)"revision")) == 0){//ao encontrar a revisao
            		parse_Revision(data,doc,cur); //chama a funçao para fazer parse a revisao
        }
    }
};


static void parse_Revision (char** data, xmlDocPtr doc, xmlNodePtr cur){
    xmlChar* info;
    xmlNodePtr aux;
    int text_size,words = 0;
    cur = cur->xmlChildrenNode;

    for(;cur;cur = cur->next){
        if((xmlStrcmp(cur->name, (const xmlChar*)"id")) == 0){
            info = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            data[2] = strdup(info);
            xmlFree(info);
        }

        else if((xmlStrcmp(cur->name, (const xmlChar*)"timestamp")) == 0){
            info = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            data[4] = strdup(info);
            xmlFree(info);
        }

        else if((xmlStrcmp(cur->name, (const xmlChar*)"contributor")) == 0){
            aux = cur->xmlChildrenNode;
            for(;aux;aux = aux->next){
              
                if((xmlStrcmp(aux->name, (const xmlChar*)"username")) == 0){
                    info = xmlNodeListGetString(doc,aux->xmlChildrenNode,1);
                    data[5] = strdup(info);
                    xmlFree(info);
                    
                }

                if((xmlStrcmp(aux->name, (const xmlChar*)"id")) == 0){
                    info = xmlNodeListGetString(doc,aux->xmlChildrenNode,1);
                    data[6] = strdup(info);
                    xmlFree(info);
                    
                }
                if((xmlStrcmp(aux->name, (const xmlChar*)"ip")) == 0){//se for ip criamos uma flag para usar ao inserir
                	data[6] = "-68";
                	data[5] = "-37";
                }
                

        }
    }

        else if((xmlStrcmp(cur->name, (const xmlChar*)"text")) == 0 && cur->properties != NULL) {
            int len,bytes=0;
            info = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            len = word_byte_count(info,&bytes); //conta o num de palavras, enquanto obtemos o lenght do texto
            data[3] = malloc(10);
            data[7] = malloc(10);
            snprintf(data[3],10,"%d",len);  
			snprintf(data[7],10,"%d",bytes);
            xmlFree(info);
            }
        }
    }

static void insere(char** d, CAT_A artigos, CAT_C contribuidores){
    int conta = 0;
    long a_id = strtol(d[1],NULL,10);
    char* a_title = strdup(d[0]);

    long size_b = strtol(d[7],NULL,10);
    long size_w = strtol(d[3],NULL,10);

    long r_id = strtol(d[2],NULL,10);
    
    long c_id = strtol(d[6],NULL,10);
   

    // Inserir Artigos
        // Verifica se o artigo existe

    if(lookUpArtigo(artigos,a_id)){
        Artigo aux_A = (Artigo) getArtigo(artigos,a_id);
        CAT_R aux_R = (CAT_R) getArtigoRevisoes(aux_A);


        // Verifica se é preciso dar update ao titulo, maior 
        // numero de bytes ou maior numero de palavras
 
        aux_A = update_A(aux_A,a_title,size_b,size_w);
        artigos = updateCAT_A(artigos,aux_A,a_id);
        
        /*Verifica se a revisao já existe. Caso não exista,
          adiciona, caso contrario incrementa nos duplicados.*/

        	if(!(existeRevisao(aux_R,r_id))){
            char* r_tstamp = strdup(d[4]);
            Revisao r = newRevisao(r_tstamp);

            aux_A = addRevisao(aux_A,r,r_id);
            artigos = updateCAT_A(artigos,aux_A,a_id);

            free(r_tstamp);


        	}else{
                artigoDuplicado(artigos,a_id);
                
            }
        
    }
    else{   //caso nao encontre o artigo  
        	char* r_tstamp = strdup(d[4]);
        	CAT_R r = initCatRevisao();//inicia uma AVL de revisoes
        	Revisao aux_R = newRevisao(r_tstamp); //inicia uma Revisao guardando a sua timestamp
        	Artigo aux_A = newArtigo(a_title,size_b,size_w,r);//Inicia um artigo
        	aux_A = addRevisao(aux_A,aux_R,r_id);//insere a revisao no Artigo
      		artigos = insertArtigo(artigos,a_id,aux_A);//insere o artigo no catalogo de Artigos
      		free(r_tstamp);
      		
    	
    	}
    // Inserir Contribuidores
    if(d[6] != "-68"){
    	if(lookUpContribuidor(contribuidores,c_id)){ //se encontrar Contribuidor
            Contribuidor aux_C = (Contribuidor) getContribuidor(contribuidores,c_id); //get do Contribuidor
            aux_C = addContribuicao(aux_C);//adicionar 1 contribuiçao ao Contribuidor
            updateCAT_C(contribuidores,aux_C,c_id);//Update da estrutura Contribuidor no catalogo
   		}
   	
   		else{//se ainda nao existir contribuidor
            char* c_username = strdup(d[5]);
   			Contribuidor aux_C = newContribuidor(c_username);//Cria novo contribuidor
        	insertContribuidor(contribuidores,aux_C,c_id);//Insere o contribuidor no catalogo
            free(c_username);
   		}
   	}

   	free(a_title);
    incAllCAT_A(artigos);//conta todas as pages(ALL Artticles)
}  