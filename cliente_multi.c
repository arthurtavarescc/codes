#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define TAMANHO_BUFFER 1024

int socket_cliente;
char nome_usuario[50];  // Nome do usuário

// Função para receber mensagens do servidor em uma thread separada
void *receber_mensagens(void *arg) {
    char buffer[TAMANHO_BUFFER];
    while (1) {
        int bytes_recebidos = recv(socket_cliente, buffer, TAMANHO_BUFFER, 0);
        if (bytes_recebidos <= 0) {
            printf("Desconectado do servidor.\n");
            close(socket_cliente);
            exit(0);
        }
        buffer[bytes_recebidos] = '\0'; // Garante que a string termine corretamente
        printf("%s\n", buffer); // Exibe a mensagem recebida
    }
    return NULL;
}

int main() {
    struct sockaddr_in endereco_servidor;
    
    // Solicita o nome do usuário
    printf("Digite seu nome: ");
    fgets(nome_usuario, 50, stdin);
    nome_usuario[strcspn(nome_usuario, "\n")] = 0;  // Remove a quebra de linha

    // Criação do socket
    socket_cliente = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_cliente == -1) {
        perror("Erro ao criar socket");
        exit(1);
    }

    // Configuração do endereço do servidor
    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_port = htons(8080);
    endereco_servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); // Conexão local

    // Conectar ao servidor
    if (connect(socket_cliente, (struct sockaddr*)&endereco_servidor, sizeof(endereco_servidor)) == -1) {
        perror("Erro ao conectar ao servidor");
        exit(1);
    }

    // Envia o nome do usuário para o servidor
    send(socket_cliente, nome_usuario, strlen(nome_usuario), 0);

    // Criar uma thread para receber mensagens do servidor
    pthread_t thread_recebimento;
    pthread_create(&thread_recebimento, NULL, receber_mensagens, NULL);

    char buffer[TAMANHO_BUFFER];
    while (1) {
        fgets(buffer, TAMANHO_BUFFER, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove a quebra de linha

        // Se o usuário digitar "sair", encerra a conexão
        if (strcmp(buffer, "sair") == 0) {
            close(socket_cliente);
            exit(0);
        }

        // Monta a mensagem com o nome do usuário
        char mensagem_formatada[TAMANHO_BUFFER];
        snprintf(mensagem_formatada, TAMANHO_BUFFER, "%s: %s", nome_usuario, buffer);

        // Envia a mensagem para o servidor
        send(socket_cliente, mensagem_formatada, strlen(mensagem_formatada), 0);
    }

    return 0;
}

