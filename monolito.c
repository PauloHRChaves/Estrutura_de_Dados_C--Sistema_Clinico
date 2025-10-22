#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//---------------------------------------------------------------
//                       LISTA ENCADEADA
//---------------------------------------------------------------

typedef struct{
    char nome[51];
    int idade;
    char CPF[12];
    char prioridade[4];

    struct Paciente *prox;
} Paciente;

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
    
    novoNo->prox = NULL;
    return novoNo;
}

Paciente* inserirElementoComeco(Paciente* lista, char nome[], int idade, char cpf[]){
    Paciente* novoNo = criarNo(nome, idade, cpf);
    novoNo->prox = lista;
    return novoNo;
}

//---------------------------------------------------------------
//                           FILA
//---------------------------------------------------------------

typedef struct {
    Paciente *inicio; 
    Paciente *fim;
    int tamanho;
} Fila;

typedef struct {
    Fila *filaPrioridade;
    Fila *filaNormal;
} FilaDuplaPrioridade;

Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));

    fila->inicio=NULL;
    fila->fim=NULL;
    fila->tamanho=0;   
    
    return fila;
}

FilaDuplaPrioridade* criarFilaDupla() {
    FilaDuplaPrioridade* fd = (FilaDuplaPrioridade*)malloc(sizeof(FilaDuplaPrioridade));
    
    if (fd == NULL) {
        return NULL;
    }
    
    fd->filaPrioridade = criarFila();
    fd->filaNormal = criarFila();
    
    if (fd->filaPrioridade == NULL || fd->filaNormal == NULL) {
        if (fd->filaPrioridade) free(fd->filaPrioridade);
        if (fd->filaNormal) free(fd->filaNormal);
        free(fd);
        return NULL;
    }
    
    return fd;
}

void enfileirarSimples(Fila* f, Paciente* novoNo) {
    if (f->inicio == NULL) {
        f->inicio = novoNo;
        f->fim = novoNo;
    } else {
        f->fim->prox = novoNo;
        f->fim = novoNo;
    }
    f->tamanho++;
}

void enfileirarDuplo(FilaDuplaPrioridade* fd, char nome[], int idade, char cpf[]){
    Paciente* novoNo = criarNo(nome, idade, cpf);

    if (novoNo == NULL) return;

    if (strcmp(novoNo->prioridade, "Sim") == 0) {
        enfileirarSimples(fd->filaPrioridade, novoNo);
    } else {
        enfileirarSimples(fd->filaNormal, novoNo);
    }
}

//---------------------------------------------------------------
//                           PILHA
//---------------------------------------------------------------

typedef struct{
	int topo; 
	int capacidade;
	Paciente **registro;
} Pilha;

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

void empilhar (Pilha *p, Paciente *atendido){
    if (p == NULL || sePilhaCheia(p)){
        printf("\n>>ERRO: Pilha cheia ou não inicializada.\n");
        return;
    }
	p->topo++;
	p->registro [p->topo] = atendido;
    printf("\n Paciente %s adicionado ao Histórico(Posição: %d).\n", atendido->nome, p->topo);

}

Pilha* desempilhar (Pilha *p ){
    if (p == NULL || sePilhaVazia(p)) {
        printf("\n> Nao ha pacientes no Historico para remover.\n");
        return NULL;
    }

    Paciente* removido = p->registro[p->topo];
    p->topo--;
    printf("\n<< Paciente %s removido do Histórico. >>\n", removido->nome);
    return removido;

}

float visualizarHistorico(Pilha *p){
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

//---------------------------------------------------------------
//                       PARTE LÓGICA
//---------------------------------------------------------------

void menu(){
    printf("\n\n_________________ MENU _________________\n");
    printf("(1). Cadastrar Paciente.\n");
    printf("(2). Pacientes Cadastrados.\n");
    printf("(3). Buscar por CPF.\n");
    printf("(4). Mostrar Fila de Atendimento.\n"); //Mostrar Fila de atendimento, e solicitar inserção por CPF.
    printf("(5). Historico de atendimento.\n");
    printf("(6). Sair.\n");
    printf("\nSelecione a opcao para continuar: ");
}

Paciente*cadastrar(Paciente *lista, FilaDuplaPrioridade** gerenciadorFila){
    printf("\n\n~~~~~~~~~~ CADASTRANDO PACIENTE ~~~~~~~~~~\n\n");
    
    char nome[51];
    int idade;
    char cpf[12];

    if (*gerenciadorFila == NULL) {
        *gerenciadorFila = criarFilaDupla();
    }

    printf("Digite o nome: ");
    fgets(nome, 51, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Digite a idade: ");
    scanf("%d", &idade);
    while (getchar() != '\n');

    printf("Digite o CPF (11 digitos): ");
    fgets(cpf, 12, stdin);
    cpf[strcspn(cpf, "\n")] = 0;
    if (strlen(cpf) != 11){
        printf("\nERRO: O CPF deve ter 11 digitos. Cadastro cancelado.\n");
        return lista;
    }

    lista = inserirElementoComeco(lista, nome, idade, cpf);
    EnfileirarDuplo(*gerenciadorFila, nome, idade, cpf); 

    printf("\n> Paciente cadastrado com sucesso!\n");
    return lista;
}

void visualizarPacientes(Paciente *lista){
    printf("\n\n~~~~~~~~~ PACIENTES CADASTRADOS ~~~~~~~~~\n\n");
    if (listaVazia(lista)){
        printf("> Nao ha pacientes cadastrados\n");
        return;
    }
    else{
        Paciente *temp = lista;
        while (temp != NULL){
            printf("\n--- %s ---\n", temp->nome);
            printf("Idade: %d\n", temp->idade);
            printf("CPF: %s\n", temp->CPF);
            printf("Prioridade: %s\n", temp->prioridade);
            temp = temp->prox;
        }
    }
}

Paciente* buscarCpf(Paciente*lista){
    char buscacpf[12];

    printf("\n\n~~~~~~~~~~~~ BUSCAR POR CPF ~~~~~~~~~~~~\n\n");
    printf("Digite o CPF (11 digitos): ");
    fgets(buscacpf, 12, stdin);
    buscacpf[strcspn(buscacpf, "\n")] = 0;

    Paciente *temp = lista;
    while (temp != NULL) {
        if (strcmp(temp->CPF, buscacpf) == 0) {
            
            printf("\n--- Paciente %s:\n", temp->CPF);
            printf("Nome: %s\n", temp->nome);
            printf("Idade: %d\n", temp->idade);
            printf("Prioridade: %s\n", temp->prioridade);
            
            return temp;
        }
        temp = temp->prox;
    }
    printf("\n> CPF nao encontrado ou inexistente\n", buscacpf);
    return NULL;
}

void visualizarFilaSimples(Fila* f, const char* titulo) { 

    printf("\n\n--- %s (Tamanho: %d) ---\n", titulo, f->tamanho);
    
    Paciente *atual = f->inicio;
    int posicao = 1;
    
    while (atual != NULL) {
        printf("[%d] Nome: %s, Idade: %d, CPF: %s\n", 
               posicao++, atual->nome, atual->idade, atual->CPF); 
        atual = atual->prox;
    }
}

void visualizarFilaDupla(FilaDuplaPrioridade* fd) {
    printf("\n~~~~~~~~~~ FILA DE ATENDIMENTO ~~~~~~~~~~\n");
    if (fd == NULL) {
        printf("\n> O sistema de filas nao foi inicializado.\n");
        return;
    }
    visualizarFilaSimples(fd->filaPrioridade, "FILA DE PRIORIDADE");
    visualizarFilaSimples(fd->filaNormal, "FILA NORMAL");
}

//---------------------------------------------------------------
//                        CHAMADAS
//---------------------------------------------------------------

void iniciarSistema(){
    int option;
    Paciente *listaDePacientes = NULL;
    Fila* gerenciadorDeFila = NULL;
    FilaDuplaPrioridade* gerenciadorDeFilaDupla=NULL;
    Pilha* gerenciadorPilha=NULL;
    
    do{
        menu();
        scanf("%d", &option);
        while (getchar() != '\n');

        switch (option){
        case 1:
            listaDePacientes = cadastrar(listaDePacientes, &gerenciadorDeFilaDupla);
            break;
        case 2:
            visualizarPacientes(listaDePacientes); 
            break;
        case 3:
            buscarCpf(listaDePacientes);
            break;
        case 4:
            chamarParaFila(gerenciadorDeFila, );
            break;
        case 5:
            break; 
        case 6:
            printf("\nNADA\n");
            break;    
        case 7:
            printf("\nSaindo do programa...\n");
            break;
        default:
            printf("\nOpcao invalida. Por favor, selecione uma opcao de 1 a 4.\n");
            break;
        }
    } while (option != 6);
}

int main(){   
    printf("\n----- Bem Vindo a SyClin -----");
    iniciarSistema();

    return 0;
}