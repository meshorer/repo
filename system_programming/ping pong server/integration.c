#include <netinet/in.h>   /*sockaddr_in */
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h> /* close */

#include "udp.h"
#include "tcp.h"


#define UDP_PORT 4323
#define BUFFER_SIZE 100

int CheckMessage(char *message_to_read);


int main()
{

    struct sockaddr_in socket_address = {0};
    struct sockaddr_in src_address = {0};

    char udp_message_to_read[BUFFER_SIZE] = {0};
    char tcp_message_to_read[BUFFER_SIZE] = {0};
    char * message_to_send = "pong";

    int udp_fd = 0;
    int tcp_fd = 0;
    int client_fd = 0;

    tcp_fd = TcpCreateSocket(UDP_PORT,&socket_address);
    /*udp_fd = UdpCreateSocket(UDP_PORT,&socket_address);

    if (0 > udp_fd)
    {
        return -1;
    }*/

    if (0 > tcp_fd)
    {
        return -1;
    }


    while (1)
    { 

        /*if (0 != UdpGetMessage(udp_fd,udp_message_to_read,BUFFER_SIZE,&src_address))
        {
            return errno;
        }

        if ( -1 == CheckMessage(udp_message_to_read))
        {
            printf("exit now..\n");
            close(udp_fd);
            return 0;
        }

        if (0 == CheckMessage(udp_message_to_read))
        {
            if (-1 == UdpResponse(udp_fd,message_to_send,strlen(message_to_send)+1,&src_address))
            {
                return -1;
            }
        }*/

/*******************88*/
        client_fd = TcpGetMessage(tcp_fd,tcp_message_to_read,BUFFER_SIZE,&src_address);
     
        if ( -1 == CheckMessage(tcp_message_to_read))
        {
            printf("exit now..\n");
            close(client_fd);
            return 0;
        }

        if (0 == CheckMessage(tcp_message_to_read))
        {
            if (-1 == TcpResponse(client_fd,message_to_send,strlen(message_to_send)+1))
            {
                close(tcp_fd);
                return -1;
            }
        }
        memset(tcp_message_to_read, '\0', BUFFER_SIZE);
        memset(udp_message_to_read, '\0', BUFFER_SIZE);

    }

    close(client_fd);
    return 0;
}

int CheckMessage(char *message_to_read)
{
    if (0 == strcmp(message_to_read,"quit"))
    {
        printf("recieved %s\n",message_to_read);
        return -1;
    }

    if (0 == strcmp(message_to_read,"ping"))
    {
        printf("recieved %s\n",message_to_read);
        return 0;
    }

    return 1;
}
