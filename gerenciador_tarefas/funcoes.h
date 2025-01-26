#ifndef FUNCOES_H
#define FUNCOES_H

// Define o número máximo de tarefas que podem ser armazenadas
#define MAX_TAREFAS 100

// Enumeração para o status da tarefa: pode ser 'PENDENTE' ou 'CONCLUIDA'
typedef enum {
    PENDENTE, // Tarefa ainda não concluída
    CONCLUIDA // Tarefa já concluída
} Status;

// Estrutura para armazenar as informações de uma tarefa
typedef struct {
    char titulo[100];    // Título da tarefa (máximo 100 caracteres)
    char descricao[300]; // Descrição da tarefa (máximo 300 caracteres)
    Status status;       // Status da tarefa (PENDENTE ou CONCLUIDA)
} Tarefa;

// Função que lista todas as tarefas armazenadas
// Parâmetros:
//   tarefas[]: Array de tarefas a ser listado
//   numero_tarefas: Número total de tarefas a serem listadas
void listar_tarefas(Tarefa tarefas[], int numero_tarefas);

// Função que adiciona uma nova tarefa
// Parâmetros:
//   tarefas[]: Array de tarefas onde a nova tarefa será adicionada
//   numero_tarefas: Número total de tarefas antes de adicionar
// Retorno:
//   O novo número total de tarefas após a adição
int adicionar_tarefa(Tarefa tarefas[], int numero_tarefas);

// Função que edita uma tarefa existente
// Parâmetros:
//   tarefas[]: Array de tarefas onde a edição será realizada
//   numero_tarefas: Número total de tarefas antes da edição
// Retorno:
//   O número total de tarefas após a edição
int editar_tarefa(Tarefa tarefas[], int numero_tarefas);

// Função que remove uma tarefa existente
// Parâmetros:
//   tarefas[]: Array de tarefas de onde a tarefa será removida
//   numero_tarefas: Número total de tarefas antes da remoção
// Retorno:
//   O número total de tarefas após a remoção
int remover_tarefa(Tarefa tarefas[], int numero_tarefas);

// Função que marca uma tarefa como concluída ou pendente
// Parâmetros:
//   tarefas[]: Array de tarefas a ser marcado
//   numero_tarefas: Número total de tarefas antes de marcar
// Retorno:
//   O número total de tarefas após o status ser alterado
int marcar_tarefa(Tarefa tarefas[], int numero_tarefas);

// Função que carrega as tarefas armazenadas (do arquivo, banco de dados ou outra fonte)
// Parâmetros:
//   tarefas[]: Array onde as tarefas carregadas serão armazenadas
// Retorno:
//   O número total de tarefas carregadas
int carregar_tarefas(Tarefa tarefas[]);

// Função que salva as tarefas no armazenamento (arquivo, banco de dados ou outra fonte)
// Parâmetros:
//   tarefas[]: Array de tarefas a serem salvas
//   numero_tarefas: Número total de tarefas a ser salvo
void salvar_tarefas(Tarefa tarefas[], int numero_tarefas);

#endif

