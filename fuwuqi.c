#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main() {
    pid_t pid;
    int socket_fd, accept_fd;
    int addrlen, iBytes;
    unsigned char buf[256];
    struct sockaddr_in server, client;
    
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error--socket:");
        _exit(-1);
    }
    
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(4000);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(socket_fd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Error-bind:");
        _exit(-2);
    }
    
    if (listen(socket_fd, 5) == -1) {
        perror("Error-listen");
        _exit(-3);
    }
    
    addrlen = sizeof(client);
    for ( ; ; ) {
        if ((accept_fd = accept(socket_fd, (struct sockaddr *)&client, &addrlen)) == -1) {
            perror("Error-accept:");
            _exit(-4);
        }
        pid = fork();
        if (pid > 0) continue;
        else if (pid == -1) {
            perror("Error-fork:");
            _exit(-5);
        }
        bzero(buf, 256);
        iBytes = read(accept_fd, buf, 256);
        if (iBytes == -1) {
            perror("Error-recv:");
            _exit(-6);
        }
        printf("[ %s:%d]发来连接请求：%s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), buf);
        if (write(accept_fd, "Welcome, baby!\n", 15) == -1) {
            perror("Error-send:");
            _exit(-7);
        }
        close(accept_fd);
        _exit(0);
    }
    return 0;
}
