#include "socket_manager.h"
#include <stdio.h>

int main() {
    SocketManager* socketManager = createSocketManager();
    if (socketManager == NULL) {
        fprintf(stderr, "Failed to create socket manager\n");
        return 1;
    }

    int socket = socketManager->initializeSocket(SOCKET_TCP);
    if (socket == -1) {
        fprintf(stderr, "Failed to initialize socket\n");
        return 1;
    }

    if (socketManager->bindSocket(socket, "127.0.0.1", 8080)) {
        printf("Socket bound successfully.\n");
    }

    // Clean up
    socketManager->closeSocket(socket);
    free(socketManager);

    return 0;
}

