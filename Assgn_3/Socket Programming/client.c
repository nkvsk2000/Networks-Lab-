// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    switch (argc ){
        case 3:
            break;
        default:
            //exit if input is not of the required format
            fprintf(stderr, "%s\n", "Usage : ./client <server_ipaddr> <port>");
            exit(1);
            break;
    }

    int sock = 0;
    int valread;
    struct sockaddr_in serv_addr;
    char * msg;
    char * server_ipaddr = argv[1];         //IP Address of the server given by the user
    char * port = argv[2];                  //Port of the server given by the user    
    char buffer[1024] = {0};

    //sock_stream is socket type used by TCP (i.e for connection oriented protocol)
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    // AF_INET is the address family(IP Addresses) that is used for the socket
    serv_addr.sin_family = AF_INET;
    //htons() function translates a short integer from host byte order to network byte order
    serv_addr.sin_port = htons(atoi(port));

    // Convert IPv4 and IPv6 addresses from text to binary form
    //if false server_ipaddr is stored in serv_addr.sinaddr
    if(inet_pton(AF_INET, server_ipaddr, &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    while(1)
    {
        // empty the current buffers for the new data to be recieved and sent
        memset(buffer, '\0', 1024);
        scanf("%s",msg);

        //creating socket descriptor to connect to server
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        //the client establishes a connection with server by calling connect
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }

        //sending message to server 
        send(sock , msg , strlen(msg) , 0 );
        //read the message recieved from server into buffer
        valread = read( sock , buffer, 1024);
        //printing the buffer
        printf("%s\n",buffer );
        close(sock);
    }
    return 0;
}