#include "../include/chamadas.h"

void iniciarSistema(){
    int option;
    Paciente *listaDePacientes = NULL;
    FilaDuplaPrioridade* gerenciadorFila=NULL;
    
    do{
        menu();
        scanf("%d", &option);
        while (getchar() != '\n');

        switch (option){
        case 1:
            listaDePacientes = cadastrar(listaDePacientes, &gerenciadorFila);
            break;
        case 2:
            visualizarPacientes(listaDePacientes);
            break;
        case 3:
            buscarCpf(listaDePacientes);
            break;
        case 4:
            visualizarFilaDupla(gerenciadorFila);
            break; 
        case 5:
            printf("\nNADA\n");
            break;    
        case 6:
            printf("\nSaindo do programa...\n");
            break;
        default:
            printf("\nOpcao invalida. Por favor, selecione uma opcao de 1 a 4.\n");
            break;
        }
    } while (option != 6);
}

int main(){   
    printf("\n\n----- Bem Vindo a SyClin -----");
    iniciarSistema();

    return 0;
}