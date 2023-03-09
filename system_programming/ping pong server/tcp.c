#include <sys/socket.h> /* socket*/
#include <netinet/in.h>   /*sockaddr_in, socklen_t*/
#include <errno.h>
#include <unistd.h> /* close */
#include <stdio.h>

#include "tcp.h"
extern int MAX_CLIENTS;
#define BACKLOG 10

int TcpCreateSocket(int port, struct sockaddr_in *address)
{
    int fd = 0;
    socklen_t addrlen = 0;
    int opt = 1;

    addrlen = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        return -1;
    }

    if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        printf("setsockopt failed\n");
    }  

    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_addr.s_addr =INADDR_ANY;

    if (-1 == bind(fd,(struct sockaddr *)address,addrlen))
    {
        return errno;
    } 

    if (-1 == listen(fd,1)) /* backlog defines how many pending connections will be queued up before it will be refused.*/
    {
        return errno;
    }

    return fd;
}


int AcceptNewFD(int fd,struct sockaddr_in *src_address)
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

    return client_fd;
}


int TcpRecieveMessage(int fd,void *message_to_read,size_t buflen)
{
    
    return recv(fd,message_to_read,buflen,0);
}

int TcpSendMessage(int fd,void *message_to_send,size_t buflen)
{
   return send(fd,message_to_send,buflen,0);
}
