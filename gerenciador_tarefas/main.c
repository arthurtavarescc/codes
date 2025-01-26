#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main() {
    // Cria um array de tarefas com o tamanho máximo definido por MAX_TAREFAS
    Tarefa tarefas[MAX_TAREFAS];
    
    // Carrega as tarefas armazenadas e retorna o número de tarefas
    int numero_tarefas = carregar_tarefas(tarefas);

    // Variáveis para armazenar a opção do usuário e limpar o buffer do teclado
    int opcao;
    char space;

    // Inicia o loop principal que continuará executando até que o usuário escolha sair
    do {
        // Exibe o menu para o usuário
        printf("\nGerenciador de Tarefas\n");
        printf("1. Listar Tarefas\n");
        printf("2. Adicionar Tarefa\n");
        printf("3. Editar Tarefa\n");
        printf("4. Remover Tarefa\n");
        printf("5. Marcar Tarefa como Concluída/Pendente\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        
        // Lê a opção escolhida pelo usuário
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado após a leitura

        // Realiza uma ação com base na opção escolhida
        switch (opcao) {
            case 1:
                // Exibe todas as tarefas armazenadas
                listar_tarefas(tarefas, numero_tarefas);
                getchar(); // Espera o usuário pressionar Enter antes de continuar
                system("clear"); // Limpa a tela do terminal (em sistemas Unix/Linux)
                break;

            case 2:
                // Permite adicionar uma nova tarefa à lista
                numero_tarefas = adicionar_tarefa(tarefas, numero_tarefas);
                // Exibe as tarefas após adicionar a nova
                listar_tarefas(tarefas, numero_tarefas);
                getchar(); // Espera o usuário pressionar Enter
                system("clear"); // Limpa a tela
                break;

            case 3:
                // Permite editar uma tarefa existente
                numero_tarefas = editar_tarefa(tarefas, numero_tarefas);
                getchar(); // Espera o usuário pressionar Enter
                system("clear"); // Limpa a tela
                break;

            case 4:
                // Permite remover uma tarefa
                numero_tarefas = remover_tarefa(tarefas, numero_tarefas);
                getchar(); // Espera o usuário pressionar Enter
                system("clear"); // Limpa a tela
                break;

            case 5:
                // Permite marcar uma tarefa como concluída ou pendente
                numero_tarefas = marcar_tarefa(tarefas, numero_tarefas);
                getchar(); // Espera o usuário pressionar Enter
                system("clear"); // Limpa a tela
                break;

            case 6:
                // Salva as tarefas antes de sair
                salvar_tarefas(tarefas, numero_tarefas);
                printf("Saindo...\n"); // Exibe mensagem de saída
                getchar(); // Espera o usuário pressionar Enter
                system("clear"); // Limpa a tela
                break;

            default:
                // Exibe mensagem de erro caso a opção não seja válida
                printf("Opção inválida!\n");
                getchar(); // Espera o usuário pressionar Enter
                system("clear"); // Limpa a tela
        }
    } while (opcao != 6); // Continua o loop até que o usuário escolha sair (opção 6)

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}

