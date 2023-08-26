#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    //variables
    int sockFd;
    struct sockaddr_in serverAddress;

    //socket creation
    sockFd = socket(AF_INET, SOCK_STREAM, 0); //TCP
    if (sockFd == -1){
        printf("failed to create a socket\n");
        exit(1);
    } else{
        printf("socket: %d\n", sockFd);
    }

    //configure server address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server's IP address
    serverAddress.sin_port = htons(1234); // Server's port

    //connect to the server
    if(connect(sockFd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        printf("failed to connect\n");
        exit(1);
    } else{
        printf("connected\n");
    }

    //communication -->read()
    char buf[128];
    ssize_t bytesRead = read(sockFd, buf, sizeof(buf));
    if(bytesRead > 0) {
        buf[bytesRead] = '\0'; // Null-terminate the received data
        printf("received: %s\n", buf);
    } else if (bytesRead == 0) {
        printf("connection closed by server\n");
    } else {
        printf("failed to read\n");
    }

    //close()
    close(sockFd);
    printf("socket closed\n");

    return 0;
}