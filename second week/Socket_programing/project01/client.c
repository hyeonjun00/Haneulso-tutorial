// socket() --> connect() --> recv()

#include <stdio.h>
#include <stdlib.h>     //atoi
#include <unistd.h>     // sockaddr_in, read, write
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>   


int main(void){
    
    //creat a socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify the addres for the socket

    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(1234);
    client_address.sin_addr.s_addr = INADDR_ANY;
    
   // connection request
    int connection_status; 
    connection_status = connect(client_socket, (struct sockaddr*)&client_address, sizeof(client_address));
    if (connection_status==-1){
        printf("there is some error in the connection \n\n\n");
    }
    //receive the data from the server

    char msg[256];
    recv(client_socket, &msg, sizeof(msg),0);
    printf("the server sends the data -----> %s\n", msg);
    close(client_socket);
    
    return 0;
}