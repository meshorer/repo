#include <netinet/in.h>   /*sockaddr_in */
#include <errno.h>
#include <arpa/inet.h>  /* htons*/
#include <sys/socket.h> /* socket*/
#include <sys/types.h> /* recfrom ?*/
#include <stdio.h>
#include "udp.h"

int UdpCreateSocket(int port, struct sockaddr_in *address)
{
    int fd = 0;
    socklen_t addrlen = 0;

    addrlen = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_DGRAM, 0);
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

    return fd;
}

int UdpGetMessage(int fd,void *buffer,size_t buflen,struct sockaddr_in *src_address)
{
    socklen_t addrlen = 0;
    addrlen = sizeof(struct sockaddr_in);

    if (-1 == recvfrom(fd,buffer,buflen,0,(struct sockaddr *)src_address,&addrlen))
    {
        return -1;
    }
    printf("server recieved message from UDP : %s\n",(char *)buffer);
    return 0;
}

int UdpResponse(int fd,const void *message,size_t message_len,const struct sockaddr_in *dest_address)
{
    socklen_t addrlen = 0;
    addrlen = sizeof(struct sockaddr_in);

    if (-1 == sendto(fd,message,message_len,0,(struct sockaddr *)dest_address,addrlen))
    {
        return -1;
    }

    return 0;
}