#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

typedef SOCKET socket_t;

DWORD WINAPI receive_messages(LPVOID arg) {
    socket_t sock = (socket_t)arg;
    char buffer[BUFFER_SIZE];
    int bytes;

    while ((bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes] = '\0';
        printf("%s", buffer);
    }
    return 0;
}

int main() {
    WSADATA wsa;
    socket_t sock;
    struct sockaddr_in server;
    char message[BUFFER_SIZE];

    WSAStartup(MAKEWORD(2, 2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection failed\n");
        return 1;
    }

    printf("Enter your username: ");
    fgets(message, BUFFER_SIZE, stdin);
    send(sock, message, strlen(message), 0);

    CreateThread(NULL, 0, receive_messages, (LPVOID)sock, 0, NULL);

    while (1) {
        fgets(message, BUFFER_SIZE, stdin);
        send(sock, message, strlen(message), 0);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
