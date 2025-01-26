#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

// Função que lista todas as tarefas armazenadas
// Exibe o título e a descrição das tarefas, além de mostrar se a tarefa está concluída ou não
// Parâmetros:
//   tarefas[]: Array de tarefas a ser listado
//   numero_tarefas: Número total de tarefas a serem listadas
void listar_tarefas(Tarefa tarefas[], int numero_tarefas) {
    printf("\nLista de Tarefas:\n");
    if (numero_tarefas == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }
    for (int i = 0; i < numero_tarefas; i++) {
        // Exibe o status da tarefa como 'x' se concluída ou espaço em branco se pendente
        printf("[%c] %d. %s\n", (tarefas[i].status == CONCLUIDA) ? 'x' : ' ', i + 1, tarefas[i].titulo);
        if (tarefas[i].descricao[0] != '\0') {
            printf("   Descrição: %s\n", tarefas[i].descricao);
        }
    }
}

// Função que adiciona uma nova tarefa à lista de tarefas
// Solicita ao usuário o título e a descrição da tarefa, e a marca como pendente
// Parâmetros:
//   tarefas[]: Array onde a nova tarefa será adicionada
//   numero_tarefas: Número total de tarefas antes da adição
// Retorno:
//   O novo número total de tarefas após a adição
int adicionar_tarefa(Tarefa tarefas[], int numero_tarefas) {
    if (numero_tarefas >= MAX_TAREFAS) {
        printf("Número máximo de tarefas atingido.\n");
        return numero_tarefas;
    }

    Tarefa nova_tarefa;
    printf("Digite o título da tarefa: ");
    fgets(nova_tarefa.titulo, sizeof(nova_tarefa.titulo), stdin);
    nova_tarefa.titulo[strcspn(nova_tarefa.titulo, "\n")] = 0; // Remove a nova linha

    printf("Digite a descrição da tarefa (pressione Enter para pular): ");
    fgets(nova_tarefa.descricao, sizeof(nova_tarefa.descricao), stdin);
    nova_tarefa.descricao[strcspn(nova_tarefa.descricao, "\n")] = 0; // Remove a nova linha

    nova_tarefa.status = PENDENTE; // Define a tarefa como pendente por padrão
    tarefas[numero_tarefas] = nova_tarefa;
    return numero_tarefas + 1;
}

// Função que edita uma tarefa existente
// Permite ao usuário alterar o título e a descrição de uma tarefa já cadastrada
// Parâmetros:
//   tarefas[]: Array de tarefas onde a edição será realizada
//   numero_tarefas: Número total de tarefas antes da edição
// Retorno:
//   O número total de tarefas após a edição
int editar_tarefa(Tarefa tarefas[], int numero_tarefas) {
    listar_tarefas(tarefas, numero_tarefas);  // Exibe a lista antes de editar

    int indice;
    printf("Digite o número da tarefa a ser editada: ");
    scanf("%d", &indice);
    getchar(); // Limpa o buffer

    if (indice < 1 || indice > numero_tarefas) {
        printf("Tarefa inválida!\n");
        return numero_tarefas;
    }

    indice--;  // Ajusta para índice baseado em 0

    // Permite o usuário editar o título da tarefa
    printf("Novo título (atualmente: %s): ", tarefas[indice].titulo);
    fgets(tarefas[indice].titulo, sizeof(tarefas[indice].titulo), stdin);
    tarefas[indice].titulo[strcspn(tarefas[indice].titulo, "\n")] = 0;

    // Permite o usuário editar a descrição da tarefa
    printf("Nova descrição (atualmente: %s): ", tarefas[indice].descricao);
    fgets(tarefas[indice].descricao, sizeof(tarefas[indice].descricao), stdin);
    tarefas[indice].descricao[strcspn(tarefas[indice].descricao, "\n")] = 0;

    return numero_tarefas;
}

// Função que remove uma tarefa existente
// Permite ao usuário remover uma tarefa da lista
// Parâmetros:
//   tarefas[]: Array de tarefas de onde a tarefa será removida
//   numero_tarefas: Número total de tarefas antes da remoção
// Retorno:
//   O número total de tarefas após a remoção
int remover_tarefa(Tarefa tarefas[], int numero_tarefas) {
    listar_tarefas(tarefas, numero_tarefas);  // Exibe a lista antes de remover

    int indice;
    printf("Digite o número da tarefa a ser removida: ");
    scanf("%d", &indice);

    if (indice < 1 || indice > numero_tarefas) {
        printf("Tarefa inválida!\n");
        return numero_tarefas;
    }

    indice--;  // Ajusta para índice baseado em 0

    // Move as tarefas seguintes para "fechar" o espaço da tarefa removida
    for (int i = indice; i < numero_tarefas - 1; i++) {
        tarefas[i] = tarefas[i + 1];
    }

    return numero_tarefas - 1;
}

// Função que marca uma tarefa como concluída ou pendente
// Alterna o status de uma tarefa entre PENDENTE e CONCLUIDA
// Parâmetros:
//   tarefas[]: Array de tarefas a ser marcado
//   numero_tarefas: Número total de tarefas antes de marcar
// Retorno:
//   O número total de tarefas após a alteração do status
int marcar_tarefa(Tarefa tarefas[], int numero_tarefas) {
    listar_tarefas(tarefas, numero_tarefas);  // Exibe a lista antes de marcar

    int indice;
    printf("Digite o número da tarefa a ser marcada: ");
    scanf("%d", &indice);

    if (indice < 1 || indice > numero_tarefas) {
        printf("Tarefa inválida!\n");
        return numero_tarefas;
    }

    indice--;  // Ajusta para índice baseado em 0
    // Alterna o status da tarefa entre PENDENTE e CONCLUIDA
    tarefas[indice].status = (tarefas[indice].status == PENDENTE) ? CONCLUIDA : PENDENTE;

    return numero_tarefas;
}

// Função que carrega as tarefas armazenadas de um arquivo
// Lê as tarefas de um arquivo binário "tarefas.dat" e as armazena no array tarefas
// Parâmetros:
//   tarefas[]: Array onde as tarefas carregadas serão armazenadas
// Retorno:
//   O número total de tarefas carregadas
int carregar_tarefas(Tarefa tarefas[]) {
    FILE *file = fopen("tarefas.dat", "rb");
    if (!file) return 0;  // Se não encontrar o arquivo, retorna 0 tarefas.

    int numero_tarefas = 0;
    while (fread(&tarefas[numero_tarefas], sizeof(Tarefa), 1, file)) {
        numero_tarefas++;
    }
    fclose(file);
    return numero_tarefas;
}

// Função que salva as tarefas no arquivo
// Salva todas as tarefas no arquivo binário "tarefas.dat"
// Parâmetros:
//   tarefas[]: Array de tarefas a serem salvas
//   numero_tarefas: Número total de tarefas a ser salvo
void salvar_tarefas(Tarefa tarefas[], int numero_tarefas) {
    FILE *file = fopen("tarefas.dat", "wb");
    if (!file) {
        printf("Erro ao salvar as tarefas.\n");
        return;
    }
    fwrite(tarefas, sizeof(Tarefa), numero_tarefas, file);
    fclose(file);
}

