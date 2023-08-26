#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void){
    //variables
    int serversockFd, clientsockFd;
    struct sockaddr_in serverAddress, clientAddress;

    //socket creation
    serversockFd = socket(AF_INET, SOCK_STREAM,0); //TCP
    if (serversockFd == -1){
        printf("failed to create a socket\n");
        exit(1);
    }else{
        printf("socket: %d\n", serversockFd);
    }

    //bind
    memset(&serverAddress, 0, sizeof(serverAddress));  
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(1234);
    if(bind(serversockFd,(struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1){
        printf("failed to bind\n");
        exit(1);
    }else{
        printf("binding succeeded\n");
    }

    //listening
    if(listen(serversockFd,1)==-1){
        printf("failed to listen\n");
    }else{
        printf("listening succeeded\n");
    }

    //accepting
    memset(&clientAddress, 0, sizeof(clientAddress));
    socklen_t clientAddressLength = sizeof(clientAddress);
    clientsockFd = accept(serversockFd, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if(clientsockFd == -1){
        printf("failed to accept\n");
        exit(1);
    }else{
        printf("acceptance succeeded\n");
    }

    //communication -->write()
    char * msg = "socket programming in c";
    write(clientsockFd, msg, strlen(msg)); 
    printf("sent: %s\n", msg);

    //closing
    close(clientsockFd);
    printf("client socket closed\n");
    close(serversockFd);   
    printf("server socket closed\n");

    return(0);
}