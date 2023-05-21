//JOÃO PEDRO CORREIA

//!!!NOTAS:
//MEU CÓDIGO ELE ESTÁ LENDO O ARQUIVO "musicas.txt"
//NÃO TEM COMO INSERIR MANUALMENTE
#include <stdio.h>
#include <string.h>
#include "listMusic.h"

//ASSINATURAS DAS FUNÇÕES
int menu();
void limpar();
void limparBuffer();
void addFila(TLista *list, TNo* (*nodo)(TLista*, TMusica*));
void addMusica(TLista *list, TMusica *musica);
TMusica *lerArquivo(FILE *fl);
void inserirMusica(TLista *list);
void listarMusicas(TLista lista);
void caminhoEmOrdem(TNo *nodo, char *nome);
void printFila(TFila *fila);
void procurarPeloArtista(TLista *list);

//MAIN=============================================
int main(){
    TLista lista;
    iniciar(&lista);
    int opcao;

    do{
        opcao = menu();
        switch(opcao){
            case 1: inserirMusica(&lista);break;
            case 2: listarMusicas(lista);break;
            case 3: procurarPeloArtista(&lista);break;            
            //case 4:
            //case 5:
            //case 6:
        }
    }while(opcao);

    return 0;
}

//FUNCOES ==================================================
int menu(){
    int opcao;
    
    limpar();
    printf("\n0 - Sair (Encerrar Aplicação)");
    printf("\n1 - Ler Arquivo de Músicas");
    printf("\n2 - Listar Músicas Cadastradas");
    printf("\n3 - Consultar Músicas por Nome do Artista");
    printf("\n4 - Consultar Músicas por nome da Música");
    printf("\n5 - Consultar Músicas por Ano de Lançamento");
    printf("\n6 - Excluir Música específica");
    
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);
    
    return opcao;
}

//==========================================================
void limparBuffer() {
        int c;
        while((c = getchar()) != '\n' && c != EOF){}
}

//==========================================================
void limpar(){
    #ifdef __linux__
        system("clear");
    #else
        system("cls");
    #endif
}

//==========================================================
TNo *nodoCantor(TLista *list, TMusica *musica){
    return procurarNo(list->indCantor, musica->cantor);
}

//==========================================================
TNo *nodoMusica(TLista *list, TMusica *musica){
    return procurarNo(list->indMusica, musica->nomeMusica);
}

//==========================================================
//NESSA PARTE DO CODIGO EU FIZ UM PONTEIRO PARA FUNCAO 
void addFila(TLista *list, TNo* (*nodo)(TLista*, TMusica*)){
    TFila *fila = (TFila*)malloc(sizeof(TFila));
    TMusica *musica;
    TNo *no;

    musica = list->fim;
    fila->musica = musica;
    no = nodo(list, musica);
    inserirFila(&(no)->filho,fila);
    printf("\nsaiu");
}

//==========================================================
void addMusica(TLista *list, TMusica *musica){
    inserirNo(&list->indCantor, musica->cantor);
    inserirNo(&list->indMusica, musica->nomeMusica);
    inserirNaLista(list, musica);
    addFila(list, nodoMusica); //ESTOU ENVIANDO A FUNÇÃO PARA UM PONTEIRO 
    addFila(list, nodoCantor);
}

//==========================================================
TMusica *lerArquivo(FILE *fl){
    TMusica *musica=(TMusica*)malloc(sizeof(TMusica));
    fscanf(fl, "%s", musica->nomeMusica);
    fscanf(fl, "%s", musica->cantor);
    fscanf(fl, "%u", &musica->ano);
    return musica;
}

//==========================================================
void inserirMusica(TLista *list){
    FILE *fl;
    TMusica *musica;
    fl = fopen("musicas.txt","r");
     
    if(!fl){
        printf("Erro de leitura\n");
        return;
    }
    while(!feof(fl)){addMusica(list, lerArquivo(fl));}
    printf("\nArquivo lido");
    fclose(fl);
}

//==========================================================
void listarMusicas(TLista lista){
    TMusica *atual = lista.inicio;

    printf("\n(Nome   \tCantor   \tAno)");
    while(atual){
        printf("\n%s   \t%s   \t%d",atual->nomeMusica, atual->cantor, atual->ano);
        atual = atual->prox;
    }
    limparBuffer();
    getchar();
}

//==========================================================
void printFila(TFila *atual){
    while(atual){
        printf("\n%s   \t%s   \t%d",atual->musica->nomeMusica, atual->musica->cantor, atual->musica->ano);
        atual = atual->prox;
    }
}

//==========================================================
void caminhoEmOrdem(TNo *nodo, char *nome){
    if(nodo){
        caminhoEmOrdem(nodo->esq, nome);
        if(!(strcmp(nodo->nome, nome)))
            printFila(nodo->filho);
        caminhoEmOrdem(nodo->dir, nome);
    }
}

//==========================================================
void procurarPeloArtista(TLista *list){
    char nome[30];
    limparBuffer();
    limpar();

    printf("Qual o Nome do Artita: ");
    scanf("%s",nome);

    caminhoEmOrdem(list->indCantor, nome);
    limparBuffer();
    getchar();
}
