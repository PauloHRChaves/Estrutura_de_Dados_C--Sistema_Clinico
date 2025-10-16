#ifndef CHAMADAS_H
#define CHAMADAS_H

#include "../include/fila_fifo.h"

void menu();

Paciente* cadastrar(Paciente *lista, FilaDuplaPrioridade** gerenciadorFila);
void visualizarPacientes(Paciente *inicio);
Paciente* buscarCpf(Paciente* inicio);

void visualizarFilaSimples(Fila* f, const char* titulo);
void visualizarFilaDupla(FilaDuplaPrioridade* fd);

#endif