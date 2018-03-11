// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    struct sockaddr_in client_address;
	
    memset(&client_address, '0', sizeof(client_address));

    client_address.sin_family = AF_INET;
    if(inet_pton(AF_INET, "192.168.31.136", &client_address.sin_addr)<=0)printf("can't set server client_address");
    client_address.sin_port = htons( PORT );
    


    int opt = 1;
    int addrlen = sizeof(address);
    int addrlen2 = sizeof(client_address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

 	memset(&address, '0', sizeof(address));

    address.sin_family = AF_INET;
    if(inet_pton(AF_INET, "192.168.31.85", &address.sin_addr)<=0)printf("can't set server address");
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    int k;
    scanf("%d",&k);
    int j=0;
    while(1)
    {
    j++;
    if ((new_socket = accept(server_fd, (struct sockaddr *)&client_address, 
                       (socklen_t*)&addrlen2))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
     printf("%s\n",inet_ntoa(client_address.sin_addr));
    valread = read( new_socket , buffer, 1024);
    printf("%s\n%d",buffer,j );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n %d",j);
    }
    return 0;
}
