#include "socket_manager.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int linux_initializeSocket(SocketType type) {
    int sock = socket(AF_INET, type == SOCKET_TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
    return (sock < 0) ? -1 : sock;
}

bool linux_bindSocket(int socketId, const char* ipAddress, int port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress, &addr.sin_addr);
    return bind(socketId, (struct sockaddr*)&addr, sizeof(addr)) == 0;
}

bool linux_listenSocket(int socketId, int backlog) {
    return listen(socketId, backlog) == 0;
}

int linux_acceptConnection(int socketId) {
    return accept(socketId, NULL, NULL);
}

bool linux_connectSocket(int socketId, const char* remoteIp, int port) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, remoteIp, &addr.sin_addr);
    return connect(socketId, (struct sockaddr*)&addr, sizeof(addr)) == 0;
}

int linux_sendData(int socketId, const char* data, int length) {
    return send(socketId, data, length, 0);
}

int linux_receiveData(int socketId, char* buffer, int length) {
    return recv(socketId, buffer, length, 0);
}

bool linux_closeSocket(int socketId) {
    return close(socketId) == 0;
}

SocketManager* createSocketManager() {
    SocketManager* manager = (SocketManager*)malloc(sizeof(SocketManager));
    if (manager) {
        manager->initializeSocket = linux_initializeSocket;
        manager->bindSocket = linux_bindSocket;
        manager->listenSocket = linux_listenSocket;
        manager->acceptConnection = linux_acceptConnection;
        manager->connectSocket = linux_connectSocket;
        manager->sendData = linux_sendData;
        manager->receiveData = linux_receiveData;
        manager->closeSocket = linux_closeSocket;
    }
    return manager;
}

