#include <sys/socket.h> /* socket*/
#include <netinet/in.h>   /*sockaddr_in, socklen_t*/
#include <errno.h>
#include <unistd.h> /* close */
#include <stdio.h>

#include "tcp.h"

#define BACKLOG 10

int TcpCreateSocket(int port, struct sockaddr_in *address)
{
    int fd = 0;
    socklen_t addrlen = 0;

    addrlen = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        return -1;
    }

    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_addr.s_addr =INADDR_ANY;

    if (-1 == bind(fd,(struct sockaddr *)address,addrlen))
    {
        return errno;
    } 

    if (-1 == listen(fd,BACKLOG)) /* backlog defines how many pending connections will be queued up before it will be refused.*/
    {
        return errno;
    }

    return fd;
}


int TcpGetMessage(int fd,void *buffer,size_t buflen,struct sockaddr_in *src_address)
{
    int client_fd = 0;
    socklen_t addrlen = 0;
    addrlen = sizeof(struct sockaddr_in);
    
    client_fd = accept(fd,(struct sockaddr *)src_address,&addrlen);
    if (client_fd < 0)
    {
        printf("Failed to accept\n");
        return errno;
    }

    if (-1 == recv(client_fd,buffer,buflen,0))
    {
        return errno;
    }
    
    return client_fd;
}

int TcpResponse(int fd,const void *message,size_t message_len)
{
   
    if (-1 == send(fd,message,message_len,0))
    {
        return -1;
    }

    return 0;
}

