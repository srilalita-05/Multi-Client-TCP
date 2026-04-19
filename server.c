#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef SOCKET socket_t;

typedef struct {
    socket_t socket;
    char username[50];
} client_t;

client_t clients[MAX_CLIENTS];
int client_count = 0;
CRITICAL_SECTION lock;

void broadcast(const char *message, socket_t sender) {
    EnterCriticalSection(&lock);
    for (int i = 0; i < client_count; i++) {
        if (clients[i].socket != sender) {
            send(clients[i].socket, message, strlen(message), 0);
        }
    }
    LeaveCriticalSection(&lock);
}

void send_private(const char *to, const char *message, socket_t sender) {
    int found = 0;

    EnterCriticalSection(&lock);
    for (int i = 0; i < client_count; i++) {
        if (strcmp(clients[i].username, to) == 0) {
            send(clients[i].socket, message, strlen(message), 0);
            found = 1;
            break;
        }
    }
    LeaveCriticalSection(&lock);

    if (!found) {
        char error_msg[100];
        sprintf(error_msg, "User '%s' not found\n", to);
        send(sender, error_msg, strlen(error_msg), 0);
    }
}

void remove_client(socket_t fd) {
    EnterCriticalSection(&lock);
    for (int i = 0; i < client_count; i++) {
        if (clients[i].socket == fd) {
            for (int j = i; j < client_count - 1; j++) {
                clients[j] = clients[j + 1];
            }
            client_count--;
            break;
        }
    }
    LeaveCriticalSection(&lock);
}

DWORD WINAPI handle_client(LPVOID arg) {
    socket_t client = (socket_t)arg;
    char buffer[BUFFER_SIZE];
    char username[50] = "";
    int bytes;

    // First message must be username
    bytes = recv(client, buffer, BUFFER_SIZE - 1, 0);
    if (bytes <= 0) {
        closesocket(client);
        return 0;
    }
    buffer[bytes] = '\0';

    strcpy(username, buffer);
    username[strcspn(username, "\r\n")] = 0;

    EnterCriticalSection(&lock);
    clients[client_count].socket = client;
    strcpy(clients[client_count].username, username);
    client_count++;
    LeaveCriticalSection(&lock);

    char join_msg[BUFFER_SIZE];
    sprintf(join_msg, "%s joined the chat\n", username);
    broadcast(join_msg, client);

    while ((bytes = recv(client, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes] = '\0';

        if (strncmp(buffer, "/pm ", 4) == 0) {
            char target[50], msg[BUFFER_SIZE];
            sscanf(buffer + 4, "%s %[^\n]", target, msg);
            target[strcspn(target, "\r\n")] = 0;

            char private_msg[BUFFER_SIZE];
            sprintf(private_msg, "[PM] %s: %s\n", username, msg);
            send_private(target, private_msg, client);
        } else {
            char msg[BUFFER_SIZE];
            sprintf(msg, "%s: %s", username, buffer);
            broadcast(msg, client);
        }
    }

    closesocket(client);
    remove_client(client);

    char leave_msg[BUFFER_SIZE];
    sprintf(leave_msg, "%s left the chat\n", username);
    broadcast(leave_msg, client);

    return 0;
}

int main() {
    WSADATA wsa;
    socket_t server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    WSAStartup(MAKEWORD(2, 2), &wsa);
    InitializeCriticalSection(&lock);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Server running on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        CreateThread(NULL, 0, handle_client, (LPVOID)client_fd, 0, NULL);
    }

    DeleteCriticalSection(&lock);
    WSACleanup();
    return 0;
}

