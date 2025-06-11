// dmzport.c Ghostivity 2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>

volatile sig_atomic_t stop = 0;

void handle_sigint(int sig) {
    stop = 1;
}

void *forward_data(void *arg) {
    int *fds = (int *)arg;
    int from = fds[0];
    int to = fds[1];
    char buffer[4096];
    ssize_t n;

    while ((n = recv(from, buffer, sizeof(buffer), 0)) > 0) {
        send(to, buffer, n, 0);
        printf("[LOG] Forwarded %zd bytes\n", n);
    }

    shutdown(from, SHUT_RD);
    shutdown(to, SHUT_WR);
    free(fds);
    return NULL;
}

void *handle_connection(void *arg) {
    int client_sock = *(int *)arg;
    free(arg);

    // TARGET_IP and TARGET_PORT will be passed via globals
    extern char *target_ip;
    extern int target_port;

    struct sockaddr_in target_addr;
    int target_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (target_sock < 0) {
        perror("[ERR] socket");
        close(client_sock);
        return NULL;
    }

    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(target_port);
    inet_pton(AF_INET, target_ip, &target_addr.sin_addr);

    if (connect(target_sock, (struct sockaddr *)&target_addr, sizeof(target_addr)) < 0) {
        perror("[ERR] connect to target");
        close(client_sock);
        close(target_sock);
        return NULL;
    }

    printf("[LOG] Connection established: client -> target\n");

    // two directions
    pthread_t t1, t2;
    int *a1 = malloc(2 * sizeof(int));
    int *a2 = malloc(2 * sizeof(int));
    a1[0] = client_sock; a1[1] = target_sock;
    a2[0] = target_sock; a2[1] = client_sock;

    pthread_create(&t1, NULL, forward_data, a1);
    pthread_create(&t2, NULL, forward_data, a2);

    pthread_detach(t1);
    pthread_detach(t2);

    return NULL;
}

char *target_ip;
int target_port;

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "-h") == 0) {
        printf("Usage: %s DMZ_IP:PORT TARGET_IP:PORT\n", argv[0]);
        printf("Example: %s 0.0.0.0:8000 192.168.122.50:80\n", argv[0]);
        return 1;
    }

    signal(SIGINT, handle_sigint);

    // Parse DMZ
    char *dmz_host = strtok(argv[1], ":");
    int dmz_port = atoi(strtok(NULL, ":"));

    // Parse TARGET
    target_ip = strtok(argv[2], ":");
    target_port = atoi(strtok(NULL, ":"));

    int server_fd, client_fd;
    struct sockaddr_in dmz_addr;
    socklen_t addrlen = sizeof(dmz_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("[ERR] socket");
        exit(1);
    }

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    dmz_addr.sin_family = AF_INET;
    dmz_addr.sin_port = htons(dmz_port);
    inet_pton(AF_INET, dmz_host, &dmz_addr.sin_addr);

    if (bind(server_fd, (struct sockaddr *)&dmz_addr, sizeof(dmz_addr)) < 0) {
        perror("[ERR] bind");
        exit(1);
    }

    if (listen(server_fd, 5) < 0) {
        perror("[ERR] listen");
        exit(1);
    }

    printf("[INFO] Listening on %s:%d -> forwarding to %s:%d\n",
           dmz_host, dmz_port, target_ip, target_port);

    while (!stop) {
        client_fd = accept(server_fd, (struct sockaddr *)&dmz_addr, &addrlen);
        if (client_fd < 0) {
            if (errno == EINTR) break;
            perror("[ERR] accept");
            continue;
        }

        int *arg = malloc(sizeof(int));
        *arg = client_fd;
        pthread_t thread;
        pthread_create(&thread, NULL, handle_connection, arg);
        pthread_detach(thread);
    }

    printf("\n[INFO] Shutting down...\n");
    close(server_fd);
    return 0;
}

