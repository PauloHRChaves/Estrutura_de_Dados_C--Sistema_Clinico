#ifndef FILA_FIFO_H
#define FILA_FIFO_H

#include "../include/lista_encadeada.h"

typedef struct {
    Paciente *inicio; 
    Paciente *fim;
    int tamanho;
} Fila;


Fila* criarFila();
int enfileirarSimples(Fila* f, Paciente* novoNo);
Paciente* desenfileirarSimples(Fila* f);

#endif