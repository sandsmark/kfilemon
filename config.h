#define SOCK_PATH "/tmp/kfilemon_sock_path-"

char *get_socket_path() {
    char *username = cuserid(0);

    int len = sizeof(SOCK_PATH) + strlen(username) + 1;
    char *r = (char*)malloc(len);
    strcpy(r, SOCK_PATH);
    strcpy(r + sizeof(SOCK_PATH) - 1, username);

    return r;
}
