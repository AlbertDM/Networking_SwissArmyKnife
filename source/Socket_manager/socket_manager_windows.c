#include "socket_manager.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

int windows_initializeSocket(SocketType type) {
    int sock = socket(AF_INET, type == SOCKET_TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
    return (sock == INVALID_SOCKET) ? -1 : sock;
}

bool windows_bindSocket(int socketId, const char* ipAddress, int port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress, &addr.sin_addr);
    return bind(socketId, (struct sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR;
}

bool windows_listenSocket(int socketId, int backlog) {
    return listen(socketId, backlog) != SOCKET_ERROR;
}

int windows_acceptConnection(int socketId) {
    return accept(socketId, NULL, NULL);
}

bool windows_connectSocket(int socketId, const char* remoteIp, int port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, remoteIp, &addr.sin_addr);
    return connect(socketId, (struct sockaddr*)&addr, sizeof(addr)) != SOCKET_ERROR;
}

int windows_sendData(int socketId, const char* data, int length) {
    return send(socketId, data, length, 0);
}

int windows_receiveData(int socketId, char* buffer, int length) {
    return recv(socketId, buffer, length, 0);
}

bool windows_closeSocket(int socketId) {
    return closesocket(socketId) != SOCKET_ERROR;
}

SocketManager* createSocketManager() {
    static WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return NULL;
    }
    SocketManager* manager = (SocketManager*)malloc(sizeof(SocketManager));
    if (manager) {
        manager->initializeSocket = windows_initializeSocket;
        manager->bindSocket = windows_bindSocket;
        manager->listenSocket = windows_listenSocket;
        manager->acceptConnection = windows_acceptConnection;
        manager->connectSocket = windows_connectSocket;
        manager->sendData = windows_sendData;
        manager->receiveData = windows_receiveData;
        manager->closeSocket = windows_closeSocket;
    }
    return manager;
}

