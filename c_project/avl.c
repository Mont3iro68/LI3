#include "avl.h"
#include <stdlib.h>
#include <string.h> 

struct nodo{
   long valor;
   void *info;
   int height;
   struct nodo *left,*right;
};

typedef enum bfactor {LH,EH,RH} BalanceFactor;

struct avl{
	int size;
	int duplicates;
	NODO head;
};

static NODO newNODO(NODO n, long id, void *estrutura);
static NODO insertNODO(NODO n, long id, void *estrutura);
static Estrutura getEstrutura_NODO (NODO n, long id);
static NODO cloneNODO(NODO n, NODO novo);

static Boolean lookUpNODO(NODO n, long id);
static void freeNODO(NODO n, Funcao f);
static NODO updateNODO(NODO n, Estrutura e, long key);
static long getValorAUX(NODO n, long key);
static NODO next_NODO (NODO n);

static NODO tree_first_node (AVL a);
static int get_Balance(NODO n);
static int get_Height(NODO n);
static NODO rotation_Left (NODO x);
static NODO rotation_Right (NODO y);

// INIT's

AVL initAVL(){
	AVL novo = malloc(sizeof(struct avl));
	novo->head = NULL;
	novo->size = 0;
	novo->duplicates = 0;

	return novo;
}

// CREATE AND INSERT

NODO initNODO(){
	NODO novo = malloc(sizeof(struct nodo));
	novo->valor = 0;
	novo->info = NULL;
	novo->height = 1;
	novo->left = NULL;
	novo->right = NULL;

	return novo;
}

static NODO newNODO(NODO n, long id, void* estrutura){
	n = initNODO();

	n->valor = id;
	n->info = estrutura;
	return n;

}

AVL insertAVL(AVL novo, long key, void *estrutura) {
	novo->head = insertNODO(novo->head,key,estrutura);
	novo->size++;

	return novo;
}


static NODO insertNODO(NODO n, long id, void *estrutura){
	int balance;
	long m;

	if(n != NULL) {
		m = max(id,n->valor);
		if(m == n->valor) n->left = insertNODO (n->left,id,estrutura);
		else if (m == id) n->right = insertNODO (n->right,id,estrutura);
			 else return n; 
	

	//atualiza os pesos da avl

		n->height = max(get_Height(n->left), get_Height(n->right)) + 1;

	//verifica o balanceamento
		balance = get_Balance(n);

	//Right Right
		if(balance < -1 && max(id,n->right->valor) == id) return rotation_Left(n);

	//Left Left
		if(balance > 1 && max(id,n->left->valor) == n->left->valor) return rotation_Right(n);

	//Left Right
		if(balance > 1 && max(id,n->left->valor) == id){
			n->left = rotation_Left (n->left);
			return rotation_Right(n);
		}	

	//Right Left

		if(balance < -1 && max(id,n->right->valor) == n->right->valor){
			n->right= rotation_Right (n->right);
			return rotation_Left(n);
		}

	}else n = newNODO(n,id,estrutura);

	return n;
}

// LOOKUP


NODO getNodoESQ(NODO n){
	if(n) return n->left;
	else return NULL;
}

NODO getNodoDIR(NODO n){
	if(n) return n->right;
	else return NULL;
}

Boolean lookUpAVL(AVL t, long key){
	if (t==NULL) return false;
	return lookUpNODO(t->head,key);
}

static Boolean lookUpNODO(NODO n,long key){
		long m;

		if(n==NULL)return false;
		else{
			if(n->valor == key) return true;
			
			m = max(n->valor,key);
			if(m == n->valor)lookUpNODO(n->left,key);
			else lookUpNODO(n->right,key);	

		}
}
	


// UPDATE 

AVL updateAVL(AVL t, Estrutura e, long key){
	t->head = updateNODO(t->head,e,key);
	return t;
}

static NODO updateNODO(NODO n, Estrutura e, long key){
	long m;
	m = max(n->valor,key);
	if(n->valor == key){ 
		n->info = e; 
		return n;
		}
	else if(m == n->valor) updateNODO(n->left,e,key);
		 else if (m == key) updateNODO(n->right,e,key);	

	return n;
}
// GET's

int getSizeAVL(AVL t){
	return t->size;
}

int getDuplicatesAVL(AVL t){
	return t->duplicates;
}

long getValorAVL(AVL t, long key){
	return getValorAUX(t->head,key);
}

static long getValorAUX(NODO n, long key){
	if (n){
		if (n->valor == key) return n->valor;
		else if (max(key,n->valor) == key) getValorAUX(n->right,key);
			 else getValorAUX(n->left,key);
		}
	else return -1;
}

long getValorNODO(NODO n){
	return n->valor;
}

void addDuplicado(AVL t){
	t->duplicates++;
}

NODO getHead(AVL t){
	return t->head;
}

Estrutura getEstruturaAVL(AVL t, long key){
	NODO n = t->head;
	long max;

	while(n){
		max = n->valor - key;
		if (max == 0) return n->info;
		if (max < 0) n = n->right;
		else n = n->left;
	}
    return NULL;
}


Estrutura getEstrutura(NODO n){
	if(n){
	return n->info;
	}
}

static NODO tree_first_node (AVL a){

  NODO tmp = initNODO();

  if (!a->head)
    return NULL;

  tmp = a->head;

  while (tmp->left)
    tmp = tmp->left;

  return tmp;
} 

// FREE's

void freeAVL(AVL n, Funcao f){
	freeNODO(n->head,f);
	free(n);
}

static void freeNODO(NODO n, Funcao f){
	if(n){
		freeNODO(n->left,f);
		freeNODO(n->right,f);
		if(n->info) f(n->info);
	}
		free(n);
}

// CLONE's

static NODO cloneNODO(NODO n, NODO novo) {
	if(n) {
		novo = malloc(sizeof(struct nodo));
		novo->valor = n->valor;
		novo->height = n->height;
		novo->info= NULL;
		novo->right = cloneNODO(n->right,novo->right);
		novo->left=cloneNODO(n->left,novo->left);

		return novo;
	}
	return NULL;
}

AVL cloneAVL(AVL n, AVL novo){
	novo = (AVL) malloc(sizeof(struct avl));
	novo->head = cloneNODO(n->head,novo->head);
	novo->size = n->size;
	return novo; 
}

// FUNÇÕES AVL

static NODO rotation_Left(NODO x){  
     NODO y = x->right;
     NODO T2 = y->left;

     y->left = x;
     x->right = T2;
     
     x->height = max(get_Height(x->left), get_Height(x->right)) +1;
     y->height = max(get_Height(y->left), get_Height(y->right)) +1;

     return y;
 }

static NODO rotation_Right(NODO y){
     NODO x = y->left;
     NODO T2 = x->right;

     x->right = y;
     y->left = T2;

     y->height = max(get_Height(y->left), get_Height(y->right)) +1;
     x->height = max(get_Height(x->left), get_Height(x->right)) +1;

     return x;
 }

static int get_Height(NODO n){
    if (n == NULL) return 0;
    return n->height;
}

static int get_Balance(NODO n) {
    if (n == NULL) return 0;
    return get_Height(n->left) - get_Height(n->right);
}