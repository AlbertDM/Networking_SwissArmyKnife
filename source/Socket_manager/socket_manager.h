#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum {
    SOCKET_TCP,
    SOCKET_UDP,
    SOCKET_RAW,
} SocketType;

// Function pointer definitions
typedef int (*InitializeSocketFunc)(SocketType type);
typedef bool (*BindSocketFunc)(int socketId, const char* ipAddress, int port);
typedef bool (*ListenSocketFunc)(int socketId, int backlog);
typedef int (*AcceptConnectionFunc)(int socketId);
typedef bool (*ConnectSocketFunc)(int socketId, const char* remoteIp, int port);
typedef int (*SendDataFunc)(int socketId, const char* data, int length);
typedef int (*ReceiveDataFunc)(int socketId, char* buffer, int length);
typedef bool (*CloseSocketFunc)(int socketId);

typedef struct {
    InitializeSocketFunc initializeSocket;
    BindSocketFunc bindSocket;
    ListenSocketFunc listenSocket;
    AcceptConnectionFunc acceptConnection;
    ConnectSocketFunc connectSocket;
    SendDataFunc sendData;
    ReceiveDataFunc receiveData;
    CloseSocketFunc closeSocket;
} SocketManager;

// Factory function to create a platform-specific SocketManager
SocketManager* createSocketManager();

#endif // SOCKET_MANAGER_H

