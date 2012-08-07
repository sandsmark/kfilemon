#include <unistd.h>
#include <sys/socket.h>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <sys/un.h>
#include <errno.h>

#include "config.h"

int main(int argc, char **argv) {
    int s = socket(AF_UNIX, SOCK_STREAM, 0);


    sockaddr_un local;
    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    socklen_t len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (sockaddr *)&local, len) == -1) {
        printf("Unable to bind! (%s)\n", strerror(errno));
        exit(errno);
    }

    if (listen(s, 5) == -1){ // backlog of five connections possible
        printf("Unable to listen! (%s)\n", strerror(errno));
        exit(errno);
    }
    char buf[1024];
    QByteArray data;
    while (true) {
        sockaddr_un client;
        len = sizeof(sockaddr_un);
        int clientSocket = accept(s, (sockaddr*)&client, &len);

        data.clear();
        while (len = recv(clientSocket, buf, sizeof(buf), 0))
            data.append(buf, len);

        qDebug() << "Got data:" << data.split(0);

        close(clientSocket);
    }
}
