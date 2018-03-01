#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include "./headers/interface.h"

struct TCD_istruct{
	CAT_A artigos;
	CAT_C contribuidores;
};

TAD_istruct init(){
	TAD_istruct a = malloc(sizeof(struct TCD_istruct));
	a->artigos = initCatArtigos();
	a->contribuidores = initCatContribuidores();
	return a;
}

TAD_istruct load(TAD_istruct qs, int nsnaps, char* snaps_paths[]){
	int i;
	for(i=1;i<nsnaps;i++){
	parseDoc(snaps_paths[i],qs->artigos,qs->contribuidores);
	}
	return qs;
}

long all_articles(TAD_istruct qs){
	return (long)(getAllCAT_A(qs->artigos));
}

long unique_articles(TAD_istruct qs){
	return(long)getTamCatArtigos(qs->artigos);
}

long all_revisions(TAD_istruct qs){
	return(long)(getAllCAT_A(qs->artigos) - getDuplicatesCAT_A(qs->artigos));
}

char* contributor_name(long contributor_id, TAD_istruct qs){
	Contribuidor aux_C = getContribuidor(qs->contribuidores,contributor_id);		
	
	if(aux_C){	
		char* username = getUsername(aux_C);
		return (char*)username;
	}
	return NULL;
}

char* article_title(long article_id, TAD_istruct qs){
	Artigo aux_A = getArtigo(qs->artigos,article_id);

	if(aux_A){
		char* title = getTitle(aux_A);
		return title;
	}
	return NULL;
}

char* article_timestamp(long article_id, long revision_id, TAD_istruct qs){
	Artigo aux_A = getArtigo(qs->artigos,article_id);
	
	if(aux_A){ 
		AVL aux_cat = getArtigoRevisoes(aux_A);
		Revisao aux_R = getRevisao(aux_cat,revision_id);

		if(aux_R){
			char* tstamp = getTimestamp(aux_R);
			return tstamp;
		}

		
	}
	return NULL;
}

TAD_istruct clean(TAD_istruct qs){
	freeCatArtigos(qs->artigos);
	freeCatContribuidores(qs->contribuidores);
	return NULL;
}