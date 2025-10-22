#include <pilha.h>

Pilha* criarPilha(int capacidade){
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

int sePilhaVazia (Pilha *p){
    if( p == NULL || p->topo == -1 ) {
        return 1; 
    }
    return 0;   
}

int sePilhaCheia (Pilha *p){
    if( p != NULL && p->topo == p->capacidade - 1 ) {
            return 1; 
        }
    return 0; 
}

Pilha* empilhar (Pilha *p, Paciente *atendido){
    if (p == NULL){
        printf("\n>>ERRO: Pilha não inicializada.\n");
        return NULL;
    }

    if (sePilhaCheia(p)){
        printf("\n>>ATENÇÃO: Histórico cheio (Capacidade %d). O paciente mais antigo será removido para inserir o novo.\n", p->capacidade);
        
        Paciente* maisAntigo = p->registro[0];
        printf("<< Paciente %s (Mais Antigo) removido permanentemente do Histórico. >>\n", maisAntigo->nome);
        free(maisAntigo); 
        

        for (int i = 0; i < p->capacidade - 1; i++) {
            p->registro[i] = p->registro[i + 1];
        }

    } else {
        p->topo++;
    }

	p->registro [p->topo] = atendido;
    printf("\n Paciente %s adicionado ao Histórico(Posição: %d).\n", 
        atendido->nome, p->topo+1);

}

Paciente* desempilhar (Pilha *p ){
    if (p == NULL || sePilhaVazia(p)) {
        printf("\n> Nao ha pacientes no Historico para remover.\n");
        return NULL;
    }

    Paciente* removido = p->registro[p->topo];
    p->topo--;
    printf("\n<< Paciente %s removido do Histórico. >>\n", removido->nome);
    return removido;

}

void visualizarHistorico(Pilha *p){
    printf("\n\n~~~~~~~~~~~ HISTÓRICO DE ATENDIMENTO ~~~~~~~~~~~\n");
    // Verifica se a pilha existe ou está vazia.
    if (p == NULL || sePilhaVazia(p)) {
        printf("\n> O Historico esta vazio.\n");
        return;
    }
    
    printf("Capacidade: %d | Total de Atendidos: %d\n", p->capacidade, p->topo + 1);
    
    // Percorre a pilha do topo (mais recente) até a base (mais antigo)

    for (int i = p->topo; i >= 0; i--) {
        Paciente *atendido = p->registro[i];
        printf("[%d] NOME: %s, CPF: %s, Prioridade: %s\n", 
                i, atendido->nome, atendido->CPF, atendido->prioridade);
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
