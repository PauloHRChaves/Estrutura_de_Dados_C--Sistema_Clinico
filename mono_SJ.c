#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//---------------------------------------------------------------
//                       LISTA ENCADEADA
//---------------------------------------------------------------

typedef struct paciente{
    char nome[51];
    int idade;
    char CPF[12];
    bool prioridade;
    struct paciente *prox;
} Paciente;

int listaVazia(Paciente *inicio){
    return inicio == NULL;
}

Paciente *criarNo(char nome[], int idade, char cpf[]){
    Paciente *novoNo = (Paciente *)malloc(sizeof(Paciente));

    strcpy(novoNo->nome, nome);
    novoNo->idade = idade;
    strcpy(novoNo->CPF, cpf);

    if (idade >= 50) {
        novoNo->prioridade = true;

    } else {
        novoNo->prioridade = false;
    }

    novoNo->prox = NULL;
    return novoNo;
}

Paciente *inserirElementoComeco(Paciente *inicio, char nome[], int idade, char cpf[]){
    Paciente *novoNo = criarNo(nome, idade, cpf);
    novoNo->prox = inicio;
    return novoNo;
}


//---------------------------------------------------------------
//                           FILA
//---------------------------------------------------------------



//---------------------------------------------------------------
//                          PILHA
//---------------------------------------------------------------


#define MAX_SIZE 20


typedef struct{

    int itens[MAX_SIZE];
    int topo;

} Pilha;


void inicializarPilha(Pilha *bloco){
    bloco->topo = -1;
}

int pilhaCheia(Pilha *bloco){
    return bloco->topo == MAX_SIZE - 1;
}

int pilhaVazia(Pilha *bloco){
    return bloco->topo == -1;
}

void empilhar(Pilha *bloco, int valor){
    if(pilhaCheia(bloco)){
        printf("\n[Erro] Pilha cheia. Nao e possivel empilhar mais elementos.\n");
        return;
    }else{
        bloco->itens[++(bloco->topo)] = valor;
        printf("\nElemento %d empilhado com sucesso.\n", valor);
    }
}

int desempilhar(Pilha *bloco){
    if(pilhaVazia(bloco)){
        printf("\n[Erro] Pilha vazia. Nao e possivel desempilhar elementos.\n");
        return -1; 
    }else{
        return bloco->itens[(bloco->topo)--];
    }
}



void listarHistorico(Pilha *bloco){
    printf("\n\n~~~~~~~~~ Últimos Atendimentos ~~~~~~~~~\n\n");
    if(pilhaVazia(Pilha *bloco)){
        printf("\nNenhum atendimento realizado ainda.\n");
        return;
    }


}


//---------------------------------------------------------------
//                       PARTE LÓGICA
//---------------------------------------------------------------

void menu(){
    printf("\n\n~~~~~~~~~ MENU ~~~~~~~~~\n\n");
    printf("(1). Cadastrar Paciente.\n");
    printf("(2). Buscar Paciente.\n");
    printf("(3). Pacientes Cadastrados.\n");
    printf("(4). Fila de Atendimento.\n");
    printf("(5). Historico de atendimento.\n");
    printf("(6). Sair.\n");
    printf("\nSelecione a opcao para continuar: ");
}

Paciente*cadastrar(Paciente *lista){

    char nome[51];
    int idade;
    char cpf[12];
    int option;


    while (option != 2){

        printf("\n\n~~~~~~~~~ CADASTRANDO PACIENTE ~~~~~~~~~\n\n"); 



        printf("Digite o nome: ");
        fgets(nome, 51, stdin);
        nome[strcspn(nome, "\n")] = 0;

        printf("Digite a idade: ");
        scanf("%d", &idade);
        while (getchar() != '\n');

        printf("Digite o CPF (11 digitos): ");
        fgets(cpf, 12, stdin);
        cpf[strcspn(cpf, "\n")] = 0;
        
        /// ------------ Comentado para testes ------------
        /*if (strlen(cpf) != 11){
            printf("\nERRO: O CPF deve ter 11 digitos. Cadastro cancelado.\n");
            return lista;
        }*/
        
        lista = inserirElementoComeco(lista, nome, idade, cpf);
        printf("\nPaciente cadastrado com sucesso!\n");


        printf("\nDeseja cadastrar outro paciente?\n");
        printf("(1). Sim -- (2). Não: ");
        scanf("%d", &option);
        while (getchar() != '\n');
        if (option == 2){
            break;
        } else if (option != 1){
            printf("\n [Erro] Opcao invalida. Retornando ao menu principal...\n");
            break;
        }


    };

    return lista;
}

void visualizarPacientes(Paciente *inicio){
    if (listaVazia(inicio)){
        printf("\n\n----------------------------");
        printf("\n\nNao ha pacientes cadastrados.\n");
        printf("\n-----------------------------");
        return;
    }
    else{
        printf("\n\n~~~~~~~~~ PACIENTES CADASTRADOS ~~~~~~~~~\n\n");
        Paciente *temp = inicio;
        int i = 1;
        while (temp != NULL){
            printf("\n--- Paciente %d ---\n", i);
            printf("Nome: %s\n", temp->nome);
            printf("Idade: %d\n", temp->idade);
            printf("CPF: %s\n", temp->CPF);
            printf("Prioridade: %s\n", temp->prioridade ? "Sim" : "Nao");
            temp = temp->prox;
            i++;
        }
        printf("\n-----------------------------");
    }
}

Paciente *buscarPaciente(Paciente *inicio){

    char busca[12];
    printf("\n\n~~~~~~~~~ BUSCAR PACIENTE ~~~~~~~~~\n\n");

    if (listaVazia(inicio)){
        printf("\n\n----------------------------");
        printf("\n\nNão há paciente cadastrado...\n");
        printf("\n------------------------------");
        return NULL;
    }

    Paciente *temp = inicio;
    int condition = 1;
    

    while (condition == 1)
    {
        printf("\n\nDigite o CPF do paciente que deseja buscar: ");
        fgets(busca, 12, stdin);
        busca[strcspn(busca, "\n")] = 0;

        while (temp != NULL){          
            if (strcmp(temp->CPF, busca) == 0){

                printf("\n--- Paciente ---\n");
                printf("Nome: %s\n", temp->nome);
                printf("Idade: %d\n", temp->idade);
                printf("CPF: %s\n", temp->CPF);
                printf("Prioridade: %s\n", temp->prioridade ? "Sim" : "Nao");

                break;
            };

                temp = temp->prox;
        }
        if (temp == NULL){
            printf("\nPaciente com CPF %s nao encontrado.\n", busca);
        }
        
        printf("\nDeseja buscar outro paciente?\n");
        printf("(1). Sim -- (2). Não: ");
        scanf("%d", &condition);
        while (getchar() != '\n');
        printf("%d", condition);


        if (condition == 2){
            break;
        } else if (condition != 1){
            printf("\n [Erro] Opcao invalida. Retornando ao menu principal...\n");
        } 
    }
    
}


//---------------------------------------------------------------
//                        CHAMADAS
//---------------------------------------------------------------

void iniciarSistema(){
    int option;
    Paciente *listaDePacientes = NULL;
    Pilha *historicoAtendimentos = NULL;

    do{
        menu();
        scanf("%d", &option);

        while (getchar() != '\n');

        switch (option){
        case 1:
            listaDePacientes = cadastrar(listaDePacientes);
            break;
        case 2:
            buscarPaciente(listaDePacientes); 
            break;
        case 3:
            visualizarPacientes(listaDePacientes);
            break;
        case 4:
            
            break;
        case 5:
            printf("\n\n~~~~~~~~~ HISTORICO DE ATENDIMENTO ~~~~~~~~~\n\n");
            listarHistorico(historicoAtendimentos);
            break;
        case 6:
            printf("\nSaindo do programa...\n");
            break;
        default:
            printf("\nOpcao invalida. Por favor, selecione uma opcao de 1 a 4.\n");
            break;
        }
    } while (option != 4);
}

int main(){   
    printf("\n\n----- Bem Vindo a SyClin -----");
    iniciarSistema();

    return 0;
}