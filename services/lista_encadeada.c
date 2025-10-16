#include "../include/lista_encadeada.h"

// Cria um novo nó.
Paciente* criarNo(char nome[], int idade, char cpf[]){
    Paciente* novoNo = (Paciente*)malloc(sizeof(Paciente)); // <-------- Reserva um espaço na memória com mesmo tamanho do struct.

    // Absorve novos dados definindo a prioridade por idade.
    strcpy(novoNo->nome, nome);
    novoNo->idade = idade;
    strcpy(novoNo->CPF, cpf);
    if (idade >= 50) {
        strcpy(novoNo->prioridade, "Sim");
    } else {
        strcpy(novoNo->prioridade, "Nao");
    }
    // Afirma que é o ultimo nó da lista, apontando NULL.
    novoNo->prox = NULL;

    return novoNo;
}

// -------- Retorna uma lista vazia.
int listaVazia(Paciente *inicio) {
    return inicio == NULL;
}

// Insere novos nós no inicio da fila, apontando sempre para quem antes estava no inicio.
Paciente* inserirElementoComeco(Paciente* inicio, char nome[], int idade, char cpf[]){
    Paciente* novoNo = criarNo(nome, idade, cpf);
    //O novo nó nesta função, aponta para o nó do inicio da lista.
    novoNo->prox = inicio;
    return novoNo;
}

// Lista Encadeada é apenas uma estrutura flexível que pode variar suas inserções e retiradas
// tando no meio, no inicio, quanto no fim.