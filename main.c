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
TNo *nodoCantor(TLista *list, TMusica *musica);
TNo *nodoMusica(TLista *list, TMusica *musica);
void addFila(TLista *list, TNo*(*nodo)(TLista*, TMusica*));
void addMusica(TLista *list, TMusica *musica);
TMusica *lerArquivo(FILE *fl);
void inserirMusica(TLista *list);
void listarMusicas(TLista lista);
void caminhoEmOrdem(TNo *nodo, char *nome);
void printFila(TFila *fila);
void procurarPeloArtista(TLista *list);
void procurarPelaMusica(TLista *list);
void procurarNaArvore(TLista *list, void (*procurar)(TLista*));
void printListaPorAno(TMusica *musica, unsigned int ano);
void procurarPorAno(TLista *list);
void excluirMusica(TLista *list);

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
                    //NOS CASE'S 3 E 4 É PASSADO UMA FUNCAO COMO PARAMETRO
                    //NA BUSCA PELA ARVORE DO ARTISTA E PELO NOME DA MUSICA
            case 3: procurarNaArvore(&lista, procurarPeloArtista);break;            
            case 4: procurarNaArvore(&lista, procurarPelaMusica);break;            
            case 5: procurarPorAno(&lista);break;
            case 6: excluirMusica(&lista);break;
        }
    }while(opcao);

    return 0;
}

//FUNCOES ==================================================
int menu(){
    int opcao;
    
    limpar();
    printf("\n0 - Sair (Encerrar Aplicao)");
    printf("\n1 - Ler Arquivo de Musicas");
    printf("\n2 - Listar Musicas Cadastradas");
    printf("\n3 - Consultar Musicas por Nome do Artista");
    printf("\n4 - Consultar Musicas por nome da Musica");
    printf("\n5 - Consultar Musicas por Ano de Lancamento");
    printf("\n6 - Excluir Musica especifica");
    
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);
    
    return opcao;
}

//==========================================================
void limparBuffer() {
        int c;
        while((c = getchar()) != '\n'){}
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
    limparBuffer();
    getchar();
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

    printf("Qual o Nome do Artita: ");
    scanf("%s",nome);

    caminhoEmOrdem(list->indCantor, nome);
}

//==========================================================
void procurarPelaMusica(TLista *list){
    char nome[30];
    limparBuffer();

    printf("Qual o Nome da Musica: ");
    scanf("%s",nome);

    caminhoEmOrdem(list->indMusica, nome);
}

//==========================================================
void procurarNaArvore(TLista *list, void (*procurar)(TLista*)){
    limpar();

    procurar(list);

    limparBuffer();
    getchar();
}

//==========================================================
void printFilaPorAno(TMusica *musica, unsigned int ano){
    if(musica){
        if(!(musica->ano - ano))printf("\n%s   \t%s   \t%d",musica->nomeMusica, musica->cantor, musica->ano);
        printFilaPorAno(musica->prox, ano);
    }
}

//==========================================================
void procurarPorAno(TLista *list){
    limpar();
    unsigned int ano;
    TMusica *musica;

    musica = list->inicio;

    printf("Ano de Lancamento da Musica: ");
    scanf("%u",&ano);
    
    printListaPorAno(musica, ano);
    limparBuffer();
    getchar(); 
}

//==========================================================
void excluirMusica(TLista *list){

}
