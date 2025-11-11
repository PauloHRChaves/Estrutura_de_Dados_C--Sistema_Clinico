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
    if (sePilhaCheia(p)){
        printf("\n>>ATENCAO: Historico cheio (Capacidade %d). O paciente mais antigo sera removido para inserir o novo.\n", p->capacidade);
        
        Paciente* maisAntigo = p->registro[0];
        printf("\n<< Paciente %s (Mais Antigo) removido permanentemente do Historico. >>\n", maisAntigo->nome);
        free(maisAntigo); 
        

        for (int i = 0; i < p->capacidade - 1; i++) {
            p->registro[i] = p->registro[i + 1];
        }

    } else {
        p->topo++;
    }

	p->registro [p->topo] = atendido;
}
