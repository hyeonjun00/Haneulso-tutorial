#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define CLNT_MAX 10
#define BUFFSIZE 256

int clnt_socks[CLNT_MAX];
int clnt_count = 0;

pthread_mutex_t mutex;

void *clnt_connection(void *arg) {
    int clnt_sock = *((int *)arg);
    int str_len;
    char msg[BUFFSIZE];

      while ((str_len = read(clnt_sock, msg, sizeof(msg))) != -1) {
        printf("Received from client: ");
        for (int i = 0; i < str_len; i++) {
            printf("%c", msg[i]);
        }
    }
    

    pthread_mutex_lock(&mutex);
    for (int i = 0; i < clnt_count; i++) {
        if (clnt_sock == clnt_socks[i]) {
            while (i++ < clnt_count - 1)
                clnt_socks[i] = clnt_socks[i + 1];
            break;
        }
    }
    clnt_count--;
    pthread_mutex_unlock(&mutex);

    close(clnt_sock);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    pthread_mutex_init(&mutex, NULL);

    int serv_sock;
    int clnt_sock;
    pthread_t t_thread;

    int clnt_addr_size;
    struct sockaddr_in clnt_addr;

    struct sockaddr_in serv_addr;
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind error");
        return 1;
    }
    if (listen(serv_sock, 5) == -1) {
        perror("listen error");
        return 1;
    }

    while (1) {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

        pthread_mutex_lock(&mutex);
        clnt_socks[clnt_count++] = clnt_sock;
        pthread_mutex_unlock(&mutex);

        pthread_create(&t_thread, NULL, clnt_connection, &clnt_sock);
        pthread_detach(t_thread);

        // 연결 메시지를 클라이언트에게 보내는 부분을 삭제하거나 주석 처리합니다.
    }

    close(serv_sock);
    return 0;
}


//컴파일러에게 pthread 라이브러리를 링크하도록 지시하도록 gcc -o server server3.c -lpthread