#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>

int main() {
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.88.133");
    server_addr.sin_port = htons(4001);
    
    int client_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket_fd < 0) {
        perror("Create Socket Failed:");
        exit(1);
    }
    
    if (sendto(client_socket_fd, "Hello, there!", 13, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Sendto:");
        exit(2);
    }
    close(client_socket_fd);
    return 0;
}
