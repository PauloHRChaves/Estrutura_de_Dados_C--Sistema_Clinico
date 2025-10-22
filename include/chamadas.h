#ifndef CHAMADAS_H
#define CHAMADAS_H

#include "../include/fila_fifo.h"
#include "../include/pilha.h"
void menu();

Paciente* cadastrar(Paciente *lista);
Paciente* buscarCpf(Paciente* inicio);
Fila* chamarParaFila(Fila* f, Paciente* lista);
void visualizarFilaSimples(Fila* f);
void visualizarPacientes(Paciente *inicio);
void finalizarAtendimento(Pilha* p, Fila* f);
#endif