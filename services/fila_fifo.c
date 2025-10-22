#include "../include/fila_fifo.h"

Fila* criarFila(){
    // Cria uma fila vazia, sem inicio, sem fim, com tamanho 0.
    Fila* fila = (Fila*)malloc(sizeof(Fila));

    fila->inicio=NULL;
    fila->fim=NULL;
    fila->tamanho=0;   
    
    return fila;
}

int enfileirarSimples(Fila* f, Paciente* novoNo) {
    if (f == NULL || novoNo == NULL) {
        return 0; // FALHA
    }

    if (f->inicio == NULL) {
        f->inicio = novoNo;
        f->fim = novoNo;
    } else {
        f->fim->prox = novoNo;
        f->fim = novoNo;
    }
    f->tamanho++;
    return 1;
}

Paciente* desenfileirarSimples(Fila* f) {
    if (f == NULL || f->inicio == NULL) {
        printf("\n> Fila de atendimento vazia.\n");
        return NULL;
    }

    Paciente* removido = f->inicio;
    f->inicio = f->inicio->prox; // O início passa a ser o próximo elemento

    // Se a fila ficou vazia após a remoção, o fim também deve ser NULL
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    f->tamanho--;
    
    printf("\n<< Paciente %s removido da Fila. >>\n", removido->nome);
    return removido;
}
