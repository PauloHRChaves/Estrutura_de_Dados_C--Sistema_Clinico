#include "../include/lista_encadeada.h"

int listaVazia(Paciente *lista) {
    return lista == NULL;
}

Paciente* criarNo(char nome[], int idade, char cpf[]){
    Paciente* novoNo = (Paciente*)malloc(sizeof(Paciente));

    strcpy(novoNo->nome, nome);
    novoNo->idade = idade;
    strcpy(novoNo->CPF, cpf);

    if (idade >= 50) {
        strcpy(novoNo->prioridade, "Sim");
    } else {
        strcpy(novoNo->prioridade, "Nao");
    }

    novoNo->naFila = false;
    
    novoNo->prox = NULL;
    return novoNo;
}

Paciente* inserirElementoFim(Paciente* lista, char nome[], int idade, char cpf[]){
    Paciente* novoNo = criarNo(nome, idade, cpf);

    if (listaVazia(lista)) {
        return novoNo;
    }
    
    Paciente* temp = lista;
    while (temp->prox != NULL) {
        temp = temp->prox;
    }
    
    temp->prox = novoNo;
    
    return lista;
}
