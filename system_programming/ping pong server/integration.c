#include <netinet/in.h> /*sockaddr_in */
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/select.h> /* select*/
#include <unistd.h>  /* stdin_fileno, close*/

#include "udp.h"
#include "tcp.h"
#include "stdin.h"

#define UDP_PORT 4323
#define TCP_PORT 4324
#define BUFFER_SIZE 100
#define BACKLOG 10


int CheckMessage(char *message_to_read);

int main()
{

    struct sockaddr_in socket_address = {0};
    struct sockaddr_in tcp_src_address = {0};
    struct sockaddr_in udp_src_address = {0};

    char udp_message_to_read[BUFFER_SIZE] = {0};
    char tcp_message_to_read[BUFFER_SIZE] = {0};
    char stdin_message_to_read[BUFFER_SIZE] = {0};

    char *message_to_send = "pong";

    fd_set rset = {0};
    int ret_select = 0;
    int maxfd = 0;

    int udp_fd = 0;
    int tcp_fd = 0;
    int client_fd = 0;
    int i = 0;
    int client_socket[30] = {0};
    int sd = 0;
    int opt = 1;

    tcp_fd = TcpCreateSocket(TCP_PORT, &socket_address);

    if (0 > tcp_fd)
    {
        return -1;
    }
    udp_fd = UdpCreateSocket(UDP_PORT, &socket_address);

    if (0 > udp_fd)
    {
        return -1;
    }

    
    while (1)
    {
   
        FD_ZERO(&rset);

        FD_SET(udp_fd, &rset);
        FD_SET(tcp_fd, &rset);
        FD_SET(STDIN_FILENO, &rset);

        maxfd = udp_fd > tcp_fd ? udp_fd + 1 : tcp_fd + 1;

        for (i = 0; i < BACKLOG; i++)
        {
            sd = client_socket[i]; 
            if (0 < sd)
            {
                FD_SET(sd, &rset);
            }
            if (sd > maxfd)
            {
                maxfd = sd;
            }
        }

        ret_select = select(maxfd, &rset, NULL, NULL, NULL);
        if (-1 == ret_select)
        {
            return errno;
        }

        if ((ret_select < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
        
        if (FD_ISSET(tcp_fd, &rset))
        {
            
            client_fd = TcpGetMessage(tcp_fd, tcp_message_to_read, BUFFER_SIZE, &tcp_src_address);

            for (i = 0; i < BACKLOG; i++)
            {
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = client_fd;  
                    printf("Adding to list of sockets as %d\n" , i);         
                    break;  
                }
            }

            if (0 == TcpChat(client_fd,tcp_message_to_read,message_to_send,BUFFER_SIZE))
            {
                printf("one closed\n");
            }

            memset(tcp_message_to_read, '\0', BUFFER_SIZE);
        }

        if (FD_ISSET(STDIN_FILENO, &rset))
        {
            
            if (0 != StdinGetMessage(STDIN_FILENO, stdin_message_to_read, BUFFER_SIZE))
            {
                return errno;
            }

            printf("recieved: %s\n",stdin_message_to_read);

            if (-1 == CheckMessage(stdin_message_to_read))
            {
                printf("exit now..\n");
                return 0;
            }

            else if (0 == CheckMessage(stdin_message_to_read))
            {
                if (-1 == StdinResponse(STDIN_FILENO, message_to_send, strlen(message_to_send) + 1))
                {
                    return -1;
                }
            }
            memset(stdin_message_to_read, '\0', BUFFER_SIZE);

        }
        if (FD_ISSET(udp_fd, &rset))
        {
           
            if (0 != UdpGetMessage(udp_fd, udp_message_to_read, BUFFER_SIZE, &udp_src_address))
            {
                return errno;
            }

            if (-1 == CheckMessage(udp_message_to_read))
            {
                printf("exit now..\n");
                close(udp_fd);
                return 0;
            }

            else if (0 == CheckMessage(udp_message_to_read))
            {
                if (-1 == UdpResponse(udp_fd, message_to_send, strlen(message_to_send) + 1, &udp_src_address))
                {
                    return -1;
                }
                memset(udp_message_to_read, '\0', BUFFER_SIZE);
            }
        }

        /*********************/
    }
    return 0;
}

int CheckMessage(char *message_to_read)
{
    
    if (0 == strncmp(message_to_read, "quit",4))
    {
        return -1;
    }

    if (0 == strncmp(message_to_read, "ping",4))
    {
        return 0;
    }

    return 1;
}
