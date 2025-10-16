#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct paciente{
    char nome[51];
    int idade;
    char CPF[12];
    char prioridade[4];

    struct paciente *prox;
} Paciente;

int listaVazia(Paciente *inicio);
Paciente* criarNo(char nome[], int idade, char cpf[]);
Paciente* inserirElementoComeco(Paciente *inicio, char nome[], int idade, char cpf[]);

#endif