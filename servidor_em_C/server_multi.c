#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTES 10
#define TAMANHO_BUFFER 1024

typedef struct {
    int socket;
    char nome[50];
} Cliente;

Cliente clientes[MAX_CLIENTES];
int contador_clientes = 0;
pthread_mutex_t mutex_clientes = PTHREAD_MUTEX_INITIALIZER;

void enviar_mensagem_para_todos(char *mensagem, int socket_remetente) {
    pthread_mutex_lock(&mutex_clientes);
    for (int i = 0; i < contador_clientes; i++) {
        if (clientes[i].socket != socket_remetente) {
            send(clientes[i].socket, mensagem, strlen(mensagem), 0);
        }
    }
    pthread_mutex_unlock(&mutex_clientes);
}

void *lidar_com_cliente(void *arg) {
    int socket_cliente = *(int *)arg;
    char buffer[TAMANHO_BUFFER];
    char nome[50];

    // Recebe o nome do cliente
    int tamanho_nome = recv(socket_cliente, nome, 50, 0);
    if (tamanho_nome <= 0) {
        close(socket_cliente);
        return NULL;
    }
    nome[tamanho_nome] = '\0';

    // Adiciona o cliente à lista
    pthread_mutex_lock(&mutex_clientes);
    clientes[contador_clientes].socket = socket_cliente;
    strcpy(clientes[contador_clientes].nome, nome);
    contador_clientes++;
    pthread_mutex_unlock(&mutex_clientes);

    // Mensagem de entrada no chat
    char mensagem_boas_vindas[TAMANHO_BUFFER];
    snprintf(mensagem_boas_vindas, TAMANHO_BUFFER, "[%s entrou no chat]", nome);
    enviar_mensagem_para_todos(mensagem_boas_vindas, socket_cliente);

    while (1) {
        int bytes_recebidos = recv(socket_cliente, buffer, TAMANHO_BUFFER, 0);
        if (bytes_recebidos <= 0) {
            break;
        }
        buffer[bytes_recebidos] = '\0';
        enviar_mensagem_para_todos(buffer, socket_cliente);
    }

    // Cliente saiu
    close(socket_cliente);
    pthread_mutex_lock(&mutex_clientes);
    for (int i = 0; i < contador_clientes; i++) {
        if (clientes[i].socket == socket_cliente) {
            snprintf(mensagem_boas_vindas, TAMANHO_BUFFER, "[%s saiu do chat]", clientes[i].nome);
            enviar_mensagem_para_todos(mensagem_boas_vindas, socket_cliente);

            // Remove o cliente da lista
            for (int j = i; j < contador_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            contador_clientes--;
            break;
        }
    }
    pthread_mutex_unlock(&mutex_clientes);

    return NULL;
}

int main() {
    int socket_servidor, socket_cliente;
    struct sockaddr_in endereco_servidor, endereco_cliente;
    socklen_t tamanho_cliente = sizeof(endereco_cliente);

    socket_servidor = socket(AF_INET, SOCK_STREAM, 0);
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_port = htons(8080);
    endereco_servidor.sin_addr.s_addr = INADDR_ANY;

    bind(socket_servidor, (struct sockaddr*)&endereco_servidor, sizeof(endereco_servidor));
    listen(socket_servidor, MAX_CLIENTES);

    printf("Servidor rodando na porta 8080...\n");

    while (1) {
        socket_cliente = accept(socket_servidor, (struct sockaddr*)&endereco_cliente, &tamanho_cliente);
        if (socket_cliente == -1) {
            perror("Erro ao aceitar conexão");
            continue;
        }

        pthread_t thread;
        pthread_create(&thread, NULL, lidar_com_cliente, (void*)&socket_cliente);
    }

    return 0;
}

