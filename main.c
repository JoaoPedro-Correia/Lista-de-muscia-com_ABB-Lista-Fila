//JOÃO PEDRO CORREIA

//!!!NOTAS:
//MEU CÓDIGO ELE ESTÁ LENDO O ARQUIVO "musicas.txt"
//NÃO TEM COMO INSERIR MANUALMENTE
#include <stdio.h>
#include "listMusic.h"

int menu();
void limpar();
void limparBuffer();
void addMusica(TLista *list, TMusica *musica);
TMusica *lerArquivo(FILE *fl);
void inserirMusica(TLista *list);
void listarMusicas(TLista lista);

int main(){
    TLista lista;
    iniciar(&lista);
    int opcao;

    do{
        opcao = menu();
        switch(opcao){
            case 1: inserirMusica(&lista);break;
            case 2: listarMusicas(lista);break;
            //case 3:             
            //case 4:
            //case 5:
            //case 6:
        }
    }while(opcao);

    return 0;
}

int menu(){
    limpar();
    int opcao;
    printf("\n0 - Sair (Encerrar Aplicação)");
    printf("\n1 - Inserir Nova Música");
    printf("\n2 - Listar Músicas Cadastradas");
    printf("\n3 - Consultar Músicas por Nome do Artista");
    printf("\n4 - Consultar Músicas por nome da Música");
    printf("\n5 - Consultar Músicas por Ano de Lançamento (Busca Serial - sem o suporte de Índice)");
    printf("\n6 - Excluir Música específica");
    
    printf("\n\nOpcao: ");
    scanf("%d",&opcao);
    
    return opcao;
}

void limparBuffer() {
        int c;
        while ((c = getchar()) != '\n' && c != EOF){}
}

void limpar(){
    #ifdef __linux__
        system("clear");
    #else
        system("cls");
    #endif
}

void addMusica(TLista *list, TMusica *musica){
    inserirNo(&list->indCantor, musica->cantor);
    inserirNo(&list->indMusica, musica->nomeMusica);
    inserirNaLista(list, musica);
}

TMusica *lerArquivo(FILE *fl){
    TMusica *musica=(TMusica*)malloc(sizeof(TMusica));
    fscanf(fl, "%s", musica->nomeMusica);
    fscanf(fl, "%s", musica->cantor);
    fscanf(fl, "%u", &musica->ano);
    return musica;
}

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

void listarMusicas(TLista lista){
    TMusica *atual = lista.inicio;

    printf("\nEX: (Nome - Cantor - Ano)\n");
    while(atual){
        printf("\n%s - %s - %d",atual->nomeMusica, atual->cantor, atual->ano);
        atual = atual->prox;
    }
    limparBuffer();
    getchar();
}
