#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int sock_fd;
    int recv_num;
    int send_num;
    int client_len;
    char recv_buf[20];
    struct sockaddr_in addr_serv;
    struct sockaddr_in addr_client;
    
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        exit(1);
    }
    memset(&addr_serv, 0, sizeof(struct sockaddr_in));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(4001);
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    
    client_len = sizeof(struct sockaddr_in);
    if (bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(struct sockaddr_in)) < 0) {
        perror("bind");
        exit(2);
    }
    
    while (1) {
        recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_client, &client_len);
        if (recv_num < 0) {
            perror("recvfrom");
            exit(3);
        }
        else {
            recv_buf[recv_num] = '\0';
            printf("recv sucess: %s\n", recv_buf);
        }
        send_num = sendto(sock_fd, recv_buf, recv_num, 0, (struct sockaddr *)&addr_client, client_len);
        if (send_num < 0) {
            perror("sendto");
            exit(4);
        }
    }
    close(sock_fd);
    return 0;
}
