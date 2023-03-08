#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>


#define PORT 4323
#define ADDRESS_TO_CONNECT "127.0.0.1"
#define BUFFER_SIZE 1024


int main()
{
    int sock = 0; 
    struct sockaddr_in serv_addr;
    char *hello = "quit";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        return -1;
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    /*Convert IPv4 and IPv6 addresses from text to binary form*/
    if(inet_pton(AF_INET, ADDRESS_TO_CONNECT, &serv_addr.sin_addr)<=0)
    {
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    if (-1 == read( sock , buffer, BUFFER_SIZE))
    {
        return errno;
    }
    printf("buffer is %s\n",buffer );
    return 0;
}