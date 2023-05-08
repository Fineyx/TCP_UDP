#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main() {
    int socket_fd;
    int addrlen, iBytes;
    unsigned char buf[256];
    struct sockaddr_in server;
    
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error--socket:");
        _exit(-1);
    }
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(4000);
    server.sin_addr.s_addr = inet_addr("192.168.88.133");
    if (connect(socket_fd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("Error-connect:");
        _exit(-2);
    }
    
    if (write(socket_fd, "你好啊!\n", 17) == -1) {
        perror("Error-write:");
        _exit(-3);
    }
    bzero(buf, 256);
    iBytes = read(socket_fd, buf, 256);
    if (iBytes == -1) {
        perror("Error-read:");
        _exit(-4);
    }
    printf("服务器的响度：%s\n", buf);
    close(socket_fd);
    _exit(0);
    return 0;
}
