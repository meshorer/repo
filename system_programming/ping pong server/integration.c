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

    maxfd = udp_fd > tcp_fd ? udp_fd + 1 : tcp_fd + 1;
    FD_ZERO(&rset);

    while (1)
    {
        FD_SET(udp_fd, &rset);
        FD_SET(tcp_fd, &rset);
        FD_SET(STDIN_FILENO, &rset);

        ret_select = select(maxfd, &rset, NULL, NULL, NULL);
        if (-1 == ret_select)
        {
            return errno;
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

        /*******************88*/

        if (FD_ISSET(tcp_fd, &rset))
        {
            
            client_fd = TcpGetMessage(tcp_fd, tcp_message_to_read, BUFFER_SIZE, &tcp_src_address);

            if (-1 == CheckMessage(tcp_message_to_read))
            {
                printf("exit now..\n");
                close(client_fd);
                return 0;
            }

            if (0 == CheckMessage(tcp_message_to_read))
            {
                if (-1 == TcpResponse(client_fd, message_to_send, strlen(message_to_send) + 1))
                {
                    close(client_fd);
                    close(tcp_fd);
                    return -1;
                }
                memset(tcp_message_to_read, '\0', BUFFER_SIZE);
            }
        }
    }

    close(client_fd);
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
