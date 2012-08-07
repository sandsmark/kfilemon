#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "config.h"

static int (*kde__real_rename)(const char *old, const char *new) = 0;

static int serverSocket = -1;

int rename(const char *old, const char *new) {
    char* message;
    
    if (!kde__real_rename) { // We haven't set up yet
        kde__real_rename = dlsym(RTLD_NEXT, "rename");
    
        if ((message = dlerror()) != NULL) {
            printf(" *** rename dlopen failed: %s\n", message);
        }

        serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    }

    if (serverSocket != -1) {
        struct sockaddr_un remote;
        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, SOCK_PATH);
        socklen_t len = strlen(remote.sun_path) + sizeof(remote.sun_family);
        if (connect(serverSocket, (struct sockaddr*)&remote, len) != -1) {
            send(serverSocket, old, strlen(old)+1, 0);
            send(serverSocket, new, strlen(new)+1, 0);
            char *currentPath = get_current_dir_name();
            send(serverSocket, currentPath, strlen(currentPath), 0);
            free(currentPath);
        } else {
            printf(" ! Unable to connect to kfilemond! (%s)\n", strerror(errno));
        }
    } else {
        printf(" ! Unable to create kfilemon socket! (%s)\n", strerror(errno));
    }

    printf(" -- Spotted moving %s to %s\n", old, new);
    
    return kde__real_rename(old, new);
}

