#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUFFSIZE 256

void *receive_thread(void *arg) {
    int sock = *((int *)arg);
    char msg[BUFFSIZE];
    
    while (1) {
        int str_len = read(sock, msg, sizeof(msg));
        if (str_len == ) {
            break; // 서버가 연결을 끊으면 스레드 종료
        }
        for (int i = 0; i < str_len; i++) {
            putchar(msg[i]);
        }
        printf('\n'); 
    }
    
    close(sock);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <server_ip> <server_port>\n", argv[0]);
        return 1;
    }

    int sock;
    struct sockaddr_in serv_addr;
    
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("connect");
        return 1;
    }
    
    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_thread, &sock);
    
    char msg[BUFFSIZE];
    while (1) {
        printf("Enter message: ");
        fgets(msg, BUFFSIZE, stdin);
        write(sock, msg, strlen(msg));
        if (strcmp(msg, "exit\n") == 0) {
            break;
        }
    }

    pthread_join(recv_thread, NULL); // 수신 스레드 종료 대기
    close(sock);
    return 0;
}
