#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//---------------------------------------------------------------
//                       LISTA ENCADEADA
//---------------------------------------------------------------

typedef struct Paciente{
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

Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));

    fila->inicio=NULL;
    fila->fim=NULL;
    fila->tamanho=0;   
    
    return fila;
}

int enfileirarSimples(Fila* f, Paciente* novoNo) {
    if (f == NULL || novoNo == NULL) {
        return 0; // FALHA
    }

    if (f->inicio == NULL) {
        f->inicio = novoNo;
        f->fim = novoNo;
    } else {
        f->fim->prox = novoNo;
        f->fim = novoNo;
    }
    f->tamanho++;
    return 1;
}

Paciente* desenfileirarSimples(Fila* f) {
    if (f == NULL || f->inicio == NULL) {
        printf("\n> Fila de atendimento vazia.\n");
        return NULL;
    }

    Paciente* removido = f->inicio;
    f->inicio = f->inicio->prox; // O início passa a ser o próximo elemento

    // Se a fila ficou vazia após a remoção, o fim também deve ser NULL
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    f->tamanho--;
    
    printf("\n<< Paciente %s removido da Fila. >>\n", removido->nome);
    return removido;
}

//---------------------------------------------------------------
//                           PILHA
//---------------------------------------------------------------

typedef struct{
	int topo; 
	int capacidade;
	Paciente **registro;
} Pilha;

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

//---------------------------------------------------------------
//                       PARTE LÓGICA
//---------------------------------------------------------------

void menu(){
    printf("\n\n_________________ MENU _________________\n");
    printf("(1). Cadastrar Paciente.\n");
    printf("(2). Pacientes Cadastrados.\n");
    printf("(3). Buscar por CPF.\n");
    printf("(4). Fila de atendimento.\n"); //Mostrar Fila de atendimento, e solicitar inserção por CPF.
    printf("(5). Finalizar atendimento.\n");
    printf("(6). Historico de atendimento.\n");    
    printf("(7). Sair.\n");
    printf("\nSelecione a opcao para continuar: ");
}

Paciente*cadastrar(Paciente *lista){
    printf("\n\n~~~~~~~~~~ CADASTRANDO PACIENTE ~~~~~~~~~~\n\n");
    
    char nome[51];
    int idade;
    char cpf[12];

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
    //enfileirarDuplo(*gerenciadorDeFilaDupla, nome, idade, cpf); 

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
        int i = 1;
        while (temp != NULL){
            printf("\n------- [%dº Paciente] -------", i++);
            printf("\nNome: %s ---\n", temp->nome);
            printf("Idade: %d\n", temp->idade);
            printf("CPF: %s\n", temp->CPF);
            printf("Prioridade: %s\n", temp->prioridade);
            temp = temp->prox;
        }
    }
}

Paciente* buscarCpf(Paciente*lista){
    char buscacpf[12];
    int condition;

    printf("\n\n~~~~~~~~~~~~ BUSCAR POR PACIENTE ~~~~~~~~~~~~\n\n");

    if (listaVazia(lista)){

    printf("\n\n------------------------------");
    printf("\n\nNão há paciente cadastrado...\n");
    printf("\n--------------------------------");
    return NULL;

    }

    do{
            
        printf("Digite o CPF (11 digitos): ");
        fgets(buscacpf, 12, stdin);
        buscacpf[strcspn(buscacpf, "\n")] = 0;

        Paciente *temp = lista; //Define um ponteiro para a lista. 
        int posicao = 0;
        while (temp != NULL) {
            if (strcmp(temp->CPF, buscacpf) == 0) {
                
                printf("\n--- [%d]Paciente ---\n", posicao);
                printf("Nome: %s\n", temp->nome);
                printf("Idade: %d\n", temp->idade);
                printf("Prioridade: %s\n", temp->prioridade);
                
                return temp;
            }
            temp = temp->prox;
            posicao++;
        }

        if (temp == NULL){
            printf("\n> CPF nao encontrado ou inexistente\n", buscacpf);
            return NULL;
        } 

        printf("\nDeseja buscar outro paciente?\n");
        printf("(1). Sim -- (2). Não: ");
        scanf("%d", &condition);
        while (getchar() != '\n');
        printf("%d", condition);


        if (condition == 1){
            continue;
        } else if (condition != 2){
            printf("\n Retornando ao menu principal...\n");
            break;
        } 
    } while (condition == 1); 

}

void visualizarFilaSimples(Fila* f) { 
    printf("\n\n---------------------- (Pacientes na fila: %d) ----------------------\n", f->tamanho);
    
    Paciente *atual = f->inicio;
    int posicao = 1;
    
    while (atual != NULL) {
        printf("[%d] Nome: %s, Idade: %d, CPF: %s, prioridade %s\n", 
               posicao++, atual->nome, atual->idade, atual->CPF, atual->prioridade); 
        atual = atual->prox;
    }
}

Fila* chamarParaFila(Fila* f, Paciente* lista){

    char cpf[12];
    char input_condition[10]; // Buffer para ler a opção (1 ou 2) com fgets
    int condition;
    
    printf("\n ======================== CHAMAR PARA FILA ========================\n");

    if (f == NULL){
        printf("\n >> ERRO: Fila de Atendimento não inicializada.\n");
        return f;
    }

    visualizarFilaSimples(f);

    if (listaVazia(lista)) {
        printf("\n> Não há pacientes cadastrados para chamar.\n");
        return f;
    }
    

    do{
    
        printf("\nDeseja chamar um paciente para a fila?\n");
        printf("(1). Sim -- (2). Não: ");
            
            // **SOLUÇÃO DO PROBLEMA DE BUFFER: Usar fgets para ler a opção.**
        if (fgets(input_condition, 10, stdin) == NULL) {
                condition = 2; // Assume "Não" em caso de erro de leitura
                break;
        }
        
        input_condition[strcspn(input_condition, "\n")] = 0;
        condition = atoi(input_condition); // Converte a string lida para inteiro

        if (condition == 1){

            printf("\nDigite o CPF do paciente a ser chamado: ");
            fgets(cpf, 12, stdin);
            cpf[strcspn(cpf, "\n")] = 0;

            Paciente* pacienteCadastrado = NULL;
            Paciente* temp = lista; 

            while (temp != NULL) {
                if (strcmp(temp->CPF, cpf) == 0) {
                pacienteCadastrado = temp;
                break;
                }
                temp = temp->prox;
            }

            if (pacienteCadastrado != NULL) {
                        // Cria a CÓPIA do nó para a Fila (como corrigido anteriormente)
                Paciente* novoNoFila = criarNo(
                    pacienteCadastrado->nome, 
                    pacienteCadastrado->idade, 
                    pacienteCadastrado->CPF);

                enfileirarSimples(f, novoNoFila); 
                printf("\n>>> Paciente %s adicionado à fila de atendimento.\n", pacienteCadastrado->nome);
                visualizarFilaSimples(f);
            } else {
                printf("\n> ERRO: Paciente com CPF %s não encontrado nos cadastros.\n", cpf);
            }

        } else if (condition == 2){
        printf("\nRetornando ao menu principal...\n");
        return f;
        } else {
        printf("\n [Erro na Solicitação. Digite 1 ou 2.]\n");
        }

    }while(condition!=2);

        return f; 
}

void finalizarAtendimento(Pilha* p, Fila* f){
    
    printf("\n\n~~~~~~~~~~ FINALIZAR ATENDIMENTO ~~~~~~~~~~\n");
    

    if (f == NULL || f->inicio == NULL) {
        printf("> Não há pacientes na fila de atendimento.\n");
        return;
    }
        
    Paciente* atendido = desenfileirarSimples(f); 

    // if (sePilhaCheia(p)){
    //     free(p->registro[0]);
    //     for(int i = 0 ; i < p->capacidade-1; i++){
    //         p->registro[i] = p->registro[i + 1];
    //     }
    // }

    if (atendido != NULL) {
        // 2. Empilha o paciente no Histórico (utilizando a Pilha)
        empilhar(p, atendido);
        printf("\n>>> Atendimento de %s finalizado e adicionado ao Histórico.\n", atendido->nome);
    } 
  
}


//---------------------------------------------------------------
//                          CHAMADAS
//---------------------------------------------------------------

void iniciarSistema(){
    int option;
    Paciente *listaDePacientes = NULL;
    Fila *gerenciadorDeFila = criarFila();
    Pilha *gerenciadorPilha= criarPilha(2);
    
    do{
        menu();
        scanf("%d", &option);
        while (getchar() != '\n');

        switch (option){
        case 1:
            listaDePacientes = cadastrar(listaDePacientes);
            break;
        case 2:
            visualizarPacientes(listaDePacientes); 
            break;
        case 3:
            buscarCpf(listaDePacientes);
            break;
        case 4:
            chamarParaFila(gerenciadorDeFila, listaDePacientes);
            break;
        case 5:
            finalizarAtendimento(gerenciadorPilha, gerenciadorDeFila);
            break; 
        case 6:
            visualizarHistorico(gerenciadorPilha);   
            break;
        case 7:
            printf("\nSaindo do programa...\n");
            break;
        default:
            printf("\nOpcao invalida. Por favor, selecione uma opcao de 1 a 4.\n");
            break;
        }
    } while (option != 7);
}

int main(){   
    printf("\n----- Bem Vindo a SyClin -----");
    iniciarSistema();
    return 0;
}