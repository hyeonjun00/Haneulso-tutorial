#include <stdio.h>
#include <stdlib.h>  //atoi
#include <unistd.h>  // sockaddr_in, read, write
#include <arpa/inet.h>  //htonl,htons, INADDR_ANY, sockaddr_in
#include <sys/types.h>
#include <netinet/in.h>


int main(void){
    char server_message[256] = "soket programming in c";
    // creating the server socket IPv4, TCP/IP protocol
    int server_socket = socket(AF_INET, SOCK_STREAM,0);

    if (server_socket == -1) {
    printf("Socket creation failed");
    exit(1);
    }

    
    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(1234);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    //bind the IP and port to the server

    bind(server_socket,(struct sockaddr*)& server_address, sizeof(server_address));
    //server_address의 포인터를 struct 타입으로 캐스팅

    //listen at the port

    listen(server_socket, 5);
    
    // accept the incoming connection from the client
    int client_sock;
    client_sock = accept(server_socket, NULL, NULL);
    if (client_sock == -1) {
    perror("connection is failed");  //using perror()
    return 1;
    }
    //send the message on the client address
    //send(int sockfd, const void*buf, size_t len, int flags); 
    send(client_sock, server_message, sizeof(server_message),0);
    close(server_socket);

    
    return 0;
}