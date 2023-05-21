#include <stdlib.h>
#include <string.h>
#define NOME 30

//ESTRUTURA QUE TEM AS INFORMACOES DENTRO DA LISTA
typedef struct Musica{
	char cantor[NOME]; //NOME DO CANTOR
	char nomeMusica[NOME]; //NOME DA MUSICA
    unsigned int ano; //ano de producao
	struct Musica *ante; 
	struct Musica *prox;
}TMusica;

//ESTRUTURA QUE CONECTA CADA NODO COM SEUS RESPECTIVA
//ESTRUTURA DA LISTA
typedef struct filaMusica{
    TMusica *musica;
    struct filaMusica *prox;
}TFila;

//ESTRUTUTURA DA ARVORE BINARIA
typedef struct ArvoreBinaria{
    char nome[NOME];  //pode ser nome de uma musica ou cantor
    struct ArvoreBinaria *esq;
    struct ArvoreBinaria *dir;
    TFila *filho;
}TNo;

//LISTA
typedef struct tipoLista {
	TMusica *inicio;
	TMusica *fim;
	unsigned int total; //quantidade de pessoas na lista
    TNo *indMusica; //aponta para a arvore de nome de musicas
    TNo *indCantor; //aponta para a arvore com o nome do cantor
}TLista;

//=== Assinatura das Funcoes =======================================
//LISTA
void iniciar(TLista *L);
void inserirNaLista(TLista *L, TMusica *novo);
int excluirDaLista(TLista *L, char *cantor);
TMusica* procurarPosicao(int posicao, TLista *lista);
TMusica *musicacpy(TMusica *original);
//ARVORE BINARIA
TNo *procurarNo(TNo *nodo, char *str);
TNo *criarNo(char *str);
TNo *inserirNo(TNo **nodo, char *str);
TNo *removeNo(TNo *nodo, char *str);
//FILA
TFila *inserirFila(TFila **inicio, TFila *novo);

//=== Funcoes ======================================================
//======================LISTA=======================
void iniciar(TLista *L){
    //A VARIAVEL TEM QUE SER INICIADA 
    L->inicio = NULL;
	L->fim = NULL;
	L->total = 0;
    L->indCantor = NULL;
    L->indMusica = NULL;
}

void inserirNaLista(TLista *L, TMusica *novo){
   TMusica *atual = L->fim;
   
   novo->ante = NULL;
   novo->prox = NULL;
   
   if(L->inicio == NULL){
   	   //Lista est� vazia...
   	   L->inicio = novo;
   	   L->fim = novo;
   } else {
   	  novo->ante = atual;
      atual->prox = novo;
      L->fim = novo; 
   }//if...else
       
   L->total++;
}

//RETORNA UM VALOR DE CONFIRMACAO, 1 SE EXCLUIU E 0 SE N�O EXCLUIU
int excluirDaLista(TLista *L, char *cantor){
   TMusica *atual = L->inicio;
   TMusica *anterior, *posterior;
   int excluido = 0;
   
   do{
   	   if(strcmp(cantor, atual->cantor) == 0){
   	   	  //Encontrado Registro a ser exclu�do...
   	   	  anterior = atual->ante;
   	   	  posterior = atual->prox;
   	   	  
   	   	  if(posterior != NULL){
   	   	    //O registro a ser exclu�do N�O � o �ltimo da Lista.
   	   	    posterior->ante = anterior;
		  } else {
		    //O registro a ser exclu�do � o �ltimo da Lista.
		    L->fim = anterior;
		  }//if
		  
		  if(anterior != NULL){
		     //O registro a ser exclu�do N�O � o primeiro da Lista.
			 anterior->prox = posterior;	
		  } else {
		  	 //O registro a ser exclu�do � o primeiro da Lista.
		     L->inicio = posterior;
		  }//if
		  
		  free(atual); //Exclu�do registro apontado por atual.
		  
		  excluido = 1;

	   }else if(atual->prox)
           atual = atual->prox;  //move atual para o pr�ximo registro.
   }while((atual != NULL) && (excluido == 0));
   
   L->total--;
   return excluido;
}

//Procura uma pessoa pela sua posicao (valor inteiro) 
TMusica* procurarNaPosicao(int posicao, TLista *lista){
    int i=0;
    TMusica *atual = lista->inicio;
    while(i!=posicao && atual){
        i++;
        atual = atual->prox;
    }
    return atual;
}

TMusica *musicacpy(TMusica *original){
	TMusica *copia = (TMusica*)malloc(sizeof(TMusica));
    
    strcpy(copia->cantor, original->cantor);
    strcpy(copia->nomeMusica, original->nomeMusica);
    copia->ano=original->ano;
    copia->prox=NULL;
    copia->ante=NULL;

	return copia;
}
//===================================================================

//=======================ARVORE BINARIA==============================
TNo *criarNo(char *str){
    TNo *novo = (TNo*)malloc(sizeof(TNo));

    novo->dir=NULL;
    novo->esq=NULL;
    novo->filho=NULL;
    strcpy(novo->nome, str);
    
    return novo;
}

TNo *inserirNo(TNo **nodo, char *str){
    if(!(*nodo))
        (*nodo) = criarNo(str);
    else if(strcmp(str, (*nodo)->nome) < 0)
        (*nodo)->esq = inserirNo(&(*nodo)->esq, str);
    else
        (*nodo)->dir = inserirNo(&(*nodo)->dir, str);
    
    return *nodo;
}

TNo *procurarNo(TNo *nodo, char *str){
    if(!nodo)
        return NULL;
    else if(strcmp(str, (nodo)->nome) < 0)
        return procurarNo((nodo)->esq, str);
    else if(strcmp(str, (nodo)->nome) > 0)
        return procurarNo((nodo)->dir, str);
    else return nodo;
}

TNo *removeNo(TNo *nodo, char *str){
    if(!nodo) //SE O NODO ESTIVER VAZIO
        return NULL;
    else if(strcmp(str, nodo->nome) < 0)
        nodo->esq = removeNo(nodo->esq, str);
    else if(strcmp(str, nodo->nome) > 0)
        nodo->dir = removeNo(nodo->dir, str);
    else{
        if(!(nodo->esq) && !(nodo->dir)){
            free(nodo);
            nodo = NULL;
        }else if(!(nodo->esq)){
            TNo *aux = nodo;
            nodo = nodo->dir;
            free(aux);
        }else if(!(nodo->dir)){
            TNo *aux = nodo;
            nodo = nodo->esq;
            free(aux);
        }else{
            TNo *aux = nodo->esq;
            while(aux->dir) aux = aux->dir;
            strcpy(nodo->nome, aux->nome);
            strcpy(aux->nome, str);
        }
    }
    return nodo;
}
//=====================================================

//========================FILA===============================
TFila *inserirFila(TFila **inicio, TFila *novo){
    if(!(*inicio)){
        *inicio = novo;
        (*inicio)->prox = NULL;
    }
    else
        (*inicio)->prox = inserirFila(&(*inicio)->prox, novo);
    return *inicio;
}
