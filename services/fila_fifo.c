#include "../include/fila_fifo.h"

Fila* criarFila(){
    // Cria uma fila vazia, sem inicio, sem fim, com tamanho 0.
    Fila* fila = (Fila*)malloc(sizeof(Fila));

    fila->inicio=NULL;
    fila->fim=NULL;
    fila->tamanho=0;   
    
    return fila;
}

//Gerenciador das filas Normal/Prioridade.
FilaDuplaPrioridade* criarFilaDupla() {
    //
    FilaDuplaPrioridade* fd = (FilaDuplaPrioridade*)malloc(sizeof(FilaDuplaPrioridade)); // Aloca espaço na memória.
    
    //Verifica se foi criado.
    if (fd == NULL) {
        return NULL;
    }
    
    fd->filaPrioridade = criarFila();
    fd->filaNormal = criarFila();
    
    // Verifica se as filas existe, ou se há algo nelas antes de criar uma nova.
    if (fd->filaPrioridade == NULL || fd->filaNormal == NULL) {
        if (fd->filaPrioridade) free(fd->filaPrioridade);
        if (fd->filaNormal) free(fd->filaNormal);
        free(fd);
        return NULL;
    }
    
    return fd;
}

void enfileirarSimples(Fila* f, Paciente* novoNo) {
    if (f->inicio == NULL) {
        f->inicio = novoNo;
        f->fim = novoNo;
    } else {
        f->fim->prox = novoNo;
        f->fim = novoNo;
    }
    f->tamanho++;
}

void EnfileirarDuplo(FilaDuplaPrioridade* fd, char nome[], int idade, char cpf[]){
    Paciente* novoNo = criarNo(nome, idade, cpf);

    if (novoNo == NULL) return;

    if (strcmp(novoNo->prioridade, "Sim") == 0) {
        enfileirarSimples(fd->filaPrioridade, novoNo);
        
    } else {
        enfileirarSimples(fd->filaNormal, novoNo);
    }
}