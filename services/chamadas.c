#include "chamadas.h"


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

// Função a ser chamada no "visualizarFilaDupla"
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
// ------------------- Fila >>>> Pilha
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

