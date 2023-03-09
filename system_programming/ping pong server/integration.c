#include <netinet/in.h> /*sockaddr_in */
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/select.h> /* select*/
#include <unistd.h>     /* stdin_fileno, close*/

#include "udp.h"
#include "tcp.h"
#include "stdin.h"
#include "logger.h"

#define PORT 1777
#define BUFFER_SIZE 100
int MAX_CLIENTS = 2;
#define MAX_CLIENTS 2

int CheckMessage(char *message_to_read);

int main()
{

    struct timeval timeout = {0}; /* to count time if nothing happens (for select)*/

    struct sockaddr_in socket_address = {0};
    struct sockaddr_in tcp_src_address = {0};
    struct sockaddr_in udp_src_address = {0};

    char udp_message_to_read[BUFFER_SIZE] = {0};
    char tcp_message_to_read[BUFFER_SIZE] = {0};
    char stdin_message_to_read[BUFFER_SIZE] = {0};

    char *message_to_send = "pong";

    fd_set rset = {0};
    int num_fds = 0;
    int maxfd = 0;

    int udp_fd = 0;
    int tcp_fd = 0;
    int client_fd = 0;
    int i = 0;
    int client_socket[MAX_CLIENTS];
    int sd = 0;
    int recieve_retval = 0;

    tcp_fd = TcpCreateSocket(PORT, &socket_address);
    if (0 > tcp_fd)
    {
        return -1;
    }

    udp_fd = UdpCreateSocket(PORT, &socket_address);
    if (0 > udp_fd)
    {
        close(udp_fd);
        return -1;
    }

    for (i = 0; i < MAX_CLIENTS; i++)
    {
        client_socket[i] = -1;
    }

    while (1)
    {

        timeout.tv_sec = 7;
        timeout.tv_usec = 0;

        FD_ZERO(&rset);
        FD_SET(udp_fd, &rset);
        FD_SET(tcp_fd, &rset);
        FD_SET(STDIN_FILENO, &rset);

        maxfd = udp_fd > tcp_fd ? udp_fd : tcp_fd; /* needed for select function */

        for (i = 0; i < MAX_CLIENTS; i++) /* keep polling for I/O operations */
        {
            sd = client_socket[i];
            if (0 < sd)
            {
                FD_SET(sd, &rset); /* if found, set it in the select readfds set*/
            }
            if (sd > maxfd)
            {
                maxfd = sd;
            }
        }

        num_fds = select(maxfd + 1, &rset, NULL, NULL, &timeout); /* select should return the number of fd's in the sets */

        if (0 == num_fds)
        {
            LogtoFile("nothing happens for 7 seconds"); /* reval 0 means timeout expired before any file descriptors became ready */
        }

        if (-1 == num_fds)
        {
            return errno;
        }

        if (FD_ISSET(tcp_fd, &rset)) /* check if the master tcp file descriptor is still present in the set */
        {

            client_fd = AcceptNewFD(tcp_fd, &tcp_src_address); /* accept the new connection in a new fd   */

            for (i = 0; i < MAX_CLIENTS; i++) /* find a free element in the clients array and assign the new fd there */
            {
                if (client_socket[i] == -1)
                {
                    client_socket[i] = client_fd;
                    printf("Adding to list of sockets as %d\n", i);
                    break;
                }
            }
        }
        
        for (i = 0; i < MAX_CLIENTS; i++)   /* check if there is a fd in the set and ready */
        {
            sd = client_socket[i];
            if (FD_ISSET(sd, &rset))
            {
                recieve_retval = TcpRecieveMessage(sd, tcp_message_to_read, BUFFER_SIZE);  /* recv  */
                printf("in server %d\n", recieve_retval);
                if (0 == recieve_retval)        /* 0 means connection died */
                {
                    printf("connnection died\n");
                    LogtoFile("tcp connect closed\n");
                    close(sd);
                    client_socket[i] = -1;
                    FD_CLR(sd, &rset);
                    continue;
                }

                if (0 > recieve_retval)
                {
                    printf("error recieving message\n");
                    return -1;
                }
               
                printf("server recieved message from TCP : %s\n", tcp_message_to_read);
                if (0 == CheckMessage(tcp_message_to_read))   /* if we reciebve ping */
                {
                    if (-1 == TcpSendMessage(sd, message_to_send, BUFFER_SIZE))  /* send */
                    {
                        printf("error sendind message\n");
                        close(sd);
                        client_socket[i] = -1;
                    }
                    printf("message sent from server\n");
                }
                else  /* if no 'ping' was recieved */
                {
                    if (-1 == TcpSendMessage(sd, "gever you need to send ping ", BUFFER_SIZE))  /* send */
                    {
                        printf("error sendind message\n");
                        close(sd);
                        client_socket[i] = -1;
                    }
                }
                memset(tcp_message_to_read, '\0', BUFFER_SIZE);  /*  clear the buffer to be able to read the next message properly */
            }
        }

        if (FD_ISSET(STDIN_FILENO, &rset))
        {

            if (0 != StdinGetMessage(STDIN_FILENO, stdin_message_to_read, BUFFER_SIZE))
            {
                return errno;
            }

            printf("recieved: %s\n", stdin_message_to_read);

            if (-1 == CheckMessage(stdin_message_to_read))
            {
                printf("exit now..\n");
                close(tcp_fd);
                close(udp_fd);

                for (i = 0; i < MAX_CLIENTS; i++)
                {
                    if (client_socket[i] != -1)
                    {
                        close(client_socket[i]);
                    }
                }
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

            if (0 == CheckMessage(udp_message_to_read))
            {
                if (-1 == UdpResponse(udp_fd, message_to_send, strlen(message_to_send) + 1, &udp_src_address))
                {
                    return -1;
                }
                memset(udp_message_to_read, '\0', BUFFER_SIZE);
            }
        }

    }
    return 0;
}

int CheckMessage(char *message_to_read)
{

    if (0 == strncmp(message_to_read, "quit", 4))
    {
        return -1;
    }

    if (0 == strncmp(message_to_read, "ping", 4))
    {
        return 0;
    }

    return 1;
}
