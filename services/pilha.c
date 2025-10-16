#include <stdio.h>
#define MAX_SIZE 20


typedef struct{

    int itens[MAX_SIZE];
    int topo;

} Pilha;


void inicializarPilha(Pilha *bloco){
    bloco->topo = -1;
}

int pilhaCheia(Pilha *bloco){
    return bloco->topo == MAX_SIZE - 1;
}

int pilhaVazia(Pilha *bloco){
    return bloco->topo == -1;
}

void empilhar(Pilha *bloco, int valor){
    if(pilhaCheia(bloco)){
        printf("\n[Erro] Pilha cheia. Nao e possivel empilhar mais elementos.\n");
        return;
    }else{
        bloco->itens[++(bloco->topo)] = valor;
        printf("\nElemento %d empilhado com sucesso.\n", valor);
    }
}

int desempilhar(Pilha *bloco){
    if(pilhaVazia(bloco)){
        printf("\n[Erro] Pilha vazia. Nao e possivel desempilhar elementos.\n");
        return -1; 
    }else{
        return bloco->itens[(bloco->topo)--];
    }
}



void listarHistorico(Pilha *bloco){
    printf("\n\n~~~~~~~~~ Últimos Atendimentos ~~~~~~~~~\n\n");

    if(pilhaVazia(bloco)){
        printf("\nNenhum atendimento realizado ainda.\n");
        return;
    }
}
    