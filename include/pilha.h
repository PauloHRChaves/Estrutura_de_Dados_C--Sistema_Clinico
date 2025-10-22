#ifndef PILHA_H
#define PILHA_H

#include "../include/lista_encadeada.h"

typedef struct{
	int topo; 
	int capacidade;
	Paciente **registro;
} Pilha;

Pilha* criarPilha(int capacidade);
int sePilhaVazia(Pilha *p);
int sePilhaCheia(Pilha *p);
Pilha* empilhar (Pilha *p, Paciente *atendido);
void visualizarHistorico(Pilha *p);

#endif