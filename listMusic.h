#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOME 25

typedef struct Musica{
	char cantor[NOME]; //NOME DO CANTOR
	char musica[NOME]; //NOME DA MUSICA
    unsigned int ano; //ano de producao
	struct Musica *ante; 
	struct Musica *prox;
}TMusica;

typedef struct filaMusica{
    char nome[NOME]; //pode ser nome de uma musica ou cantor
    TMusica *musica;
    struct filaMusica *prox;
}FMusica;

typedef struct ArvoreBinaria{
    struct ArvoreBinaria *esq;
    struct ArvoreBinaria *dir;
    FMusica *filho;
}TNo;

typedef struct tipoLista {
	TMusica *inicio;
	TMusica *fim;
	unsigned int total; //quantidade de pessoas na lista
    FMusica *indMusica; //aponta para a arvore de nome de musicas
    FMusica *indCantor; //aponta para a arvore com o nome do cantor
}TLista;

//=== Assinatura das Fun��es =======================================
void iniciar(TLista *L);
void inserirMusica(TLista *L, TMusica *pessoa);
int excluir(TLista *L, char *cantor);
TMusica* procurarPosicao(int posicao, TLista *lista);
TMusica *musicacpy(TMusica *original);

//=== Fun��es ======================================================
void iniciar(TLista *L){
    //A VARIAVEL TEM QUE SER INICIADA 
    L->inicio = NULL;
	L->fim = NULL;
	L->total = 0;
    L->indCantor = NULL;
    L->indMusica = NULL;
}

//==================================================================
void inserirMusica(TLista *L, TMusica *novo){
   
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

//==================================================================
//RETORNA UM VALOR DE CONFIRMACAO, 1 SE EXCLUIU E 0 SE N�O EXCLUIU
int excluir(TLista *L, char *cantor){
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
	   }else
           atual = atual->prox;  //move atual para o pr�ximo registro.
   }while((atual != NULL) && (excluido == 0));
   
   L->total--;
   return excluido;
}
//===================================================================
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
//===================================================================

TMusica *musicacpy(TMusica *original){
	TMusica *copia = (TMusica*)malloc(sizeof(TMusica));
    copia->cantor[0]='\0';

    strcpy(copia->cantor, original->cantor);
    strcpy(copia->musica, original->musica);
    copia->ano=original->ano;
	return copia;
}
//===================================================================
