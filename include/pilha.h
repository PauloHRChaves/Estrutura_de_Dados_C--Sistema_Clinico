#ifndef PILHA_H
#define PILHA_H

#include "../include/lista_encadeada.h"

typedef struct{
	int topo; 
	int capacidade;
	Paciente **registro;
} Pilha;

Pilha* criarPilha(Pilha *p, int capacidade);
int sePilhaVazia(Pilha *p);
int sePilhaCheia(Pilha *p);
void empilhar(Pilha *p, Paciente *atendido);
Pilha* desempilhar (Pilha *p);
float rvisualizarHistorico(Pilha *p);
#endif