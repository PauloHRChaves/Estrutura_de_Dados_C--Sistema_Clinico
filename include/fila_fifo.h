#ifndef FILA_FIFO_H
#define FILA_FIFO_H

#include "../include/lista_encadeada.h"

typedef struct {
    Paciente *inicio; 
    Paciente *fim;
    int tamanho;
} Fila;

typedef struct {
    Fila *filaPrioridade;
    Fila *filaNormal;
} FilaDuplaPrioridade;

Fila* criarFila();
FilaDuplaPrioridade* criarFilaDupla();
void enfileirarSimples(Fila* f, Paciente* novoNo);
void EnfileirarDuplo(FilaDuplaPrioridade* fd, char nome[], int idade, char cpf[]);

#endif