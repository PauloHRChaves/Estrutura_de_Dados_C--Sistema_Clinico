#include <pilha.h>

Pilha* criarPilha(Pilha *p, int capacidade){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p == NULL) return NULL;

    p->registro = (Paciente**)malloc(capacidade*sizeof(Paciente*));
    if(p->registro == NULL){
        free(p);
        return NULL;
    }
    p->topo = -1;
    p->capacidade = capacidade;

    return p;
}

int sePilhaVazia(Pilha *p){
    if( p == NULL || p->topo == -1 ) {
        return 1; 
    }
    return 0;   
}

int sePilhaCheia(Pilha *p){
    if( p != NULL && p->topo == p->capacidade - 1 ) {
            return 1; 
        }
    return 0; 
}

void empilhar(Pilha *p, Paciente *atendido){
    if (p == NULL || sePilhaCheia(p)){
        printf("\n>>ERRO: Pilha cheia ou não inicializada.\n");
        return;
    }
	p->topo++;
	p->registro [p->topo] = atendido;
    printf("\n Paciente %s adicionado ao Histórico(Posição: %d).\n", atendido->nome, p->topo);

}

Pilha* desempilhar (Pilha *p){
    if (p == NULL || sePilhaVazia(p)) {
        printf("\n> Nao ha pacientes no Historico para remover.\n");
        return NULL;
    }

    Paciente* removido = p->registro[p->topo];
    p->topo--;
    printf("\n<< Paciente %s removido do Histórico. >>\n", removido->nome);
    return removido;

}

float rvisualizarHistorico(Pilha *p){
    printf("\n\n~~~~~~~~~~~ HISTÓRICO DE ATENDIMENTO ~~~~~~~~~~~\n");
    if (p == NULL || sePilhaVazia(p)) {
        printf("> O Historico esta vazio.\n");
        return;
    }
    
    printf("Capacidade: %d | Total de Atendidos: %d\n", p->capacidade, p->topo + 1);
    
    // Percorre a pilha do topo (mais recente) até a base (mais antigo)
    for (int i = p->topo; i >= 0; i--) {
        Paciente *atendido = p->registro[i];
        printf("  [%d] NOME: %s, CPF: %s, Prioridade: %s\n", 
               i + 1, atendido->nome, atendido->CPF, atendido->prioridade);
    }
}
