#include "chamadas.h"

void menu(){
    printf("\n\n_________________ MENU _________________\n");
    printf("(1). Cadastrar paciente.\n");
    printf("(2). Pacientes cadastrados.\n");
    printf("(3). Buscar paciente.\n");
    printf("(4). Mostrar fila de atendimento.\n");
    printf("(5). Historico de atendimento.\n");
    printf("(6). Sair.\n");
    printf("\nSelecione a opcao para continuar: ");
}

Paciente*cadastrar(Paciente *lista, FilaDuplaPrioridade** gerenciadorFila){
    // ---- Declara as variáveis para introduzir as funções.
    char nome[51];
    int idade;
    char cpf[12];
    int condition;

    if (*gerenciadorFila == NULL) {
        *gerenciadorFila = criarFilaDupla();
    }

    do {

        printf("\n\n~~~~~~~~~~ CADASTRANDO PACIENTE ~~~~~~~~~~\n\n");
        

        printf("Digite o nome: ");
        fgets(nome, 51, stdin);
        nome[strcspn(nome, "\n")] = 0;

        printf("Digite a idade: ");
        scanf("%d", &idade);
        while (getchar() != '\n');

        printf("Digite o CPF (11 digitos): ");
        fgets(cpf, 12, stdin);
        cpf[strcspn(cpf, "\n")] = 0;
    
            // ---------- COMENTADO PARA TESTES --------------
        /*
        if (strlen(cpf) != 11){
            printf("\nERRO: O CPF deve ter 11 digitos. Cadastro cancelado.\n");
            return lista;
        }
        */

        lista = inserirElementoComeco(lista, nome, idade, cpf);
        EnfileirarDuplo(*gerenciadorFila, nome, idade, cpf); 

        printf("\n> Paciente cadastrado com sucesso!\n");
        
        printf("\nDeseja cadastrar outro paciente?\n");
        printf("(1). Sim -- (2). Não: ");
        scanf("%d", &condition);
        while (getchar() != '\n');

        if (condition == 1){
            printf("\nContinuando cadastro...\n");
            continue;
        } else if (condition == 2){
            printf("\nRetornando ao menu principal...\n");
            return lista;
            break;
        } else {
            printf("\n [Erro na Solicitação]\n");
            break;
        }

  } while (condition == 1);
}

void visualizarPacientes(Paciente *lista){
    printf("\n\n~~~~~~~~~ PACIENTES CADASTRADOS ~~~~~~~~~\n\n");

    if (listaVazia(lista)){
        printf("> Nao há pacientes cadastrados\n");
        return;
    } else {
        Paciente *temp = lista; //Cria um ponteiro para apontar para o primeiro elemento da lista.
        int i = 1;
        while (temp != NULL){
            printf("\n--- %s %d ---\n", temp->nome, i);
            printf("Idade: %d\n", temp->idade);
            printf("CPF: %s\n", temp->CPF);
            printf("Prioridade: %s\n", temp->prioridade);
            temp = temp->prox; //Torna-se o paontado, apontando para o proximo da lista até que não exista um próximo.
            i++;
            printf("-----------------------------------\n");
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