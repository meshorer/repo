#include <netinet/in.h> /*sockaddr_in */
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/select.h> /* select*/
#include <unistd.h>     /* stdin_fileno, close*/
#include <fcntl.h> /*fcntl*/

#include "udp.h"
#include "tcp.h"
#include "stdin.h"
#include "logger.h"

#define PORT 1777
#define BUFFER_SIZE 100
int MAX_CLIENTS = 2;
#define MAX_CLIENTS 2
#define PROBLEM_MASTER_TCP_FD -1
#define PROBLEM_UDP_FD -2
#define PROBLEM_REGULAR_TCP_FD -3

int CheckMessage(char *message_to_read, char* message_to_send);
int Destroy(int tcp_fd,int udp_fd,int *client_socket);


int main()
{

    struct timeval timeout = {0}; /* to count time if nothing happens (for select)*/

    struct sockaddr_in socket_address = {0};
    struct sockaddr_in tcp_src_address = {0};
    struct sockaddr_in udp_src_address = {0};

    char udp_message_to_read[BUFFER_SIZE] = {0};
    char tcp_message_to_read[BUFFER_SIZE] = {0};
    char stdin_message_to_read[BUFFER_SIZE] = {0};

    char message_to_send [BUFFER_SIZE] = {0};

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
        return PROBLEM_MASTER_TCP_FD;
    }

    udp_fd = UdpCreateSocket(PORT, &socket_address);
    if (0 > udp_fd)
    {
        if ( 0 != close(tcp_fd) && errno != EBADF)
        {
            return PROBLEM_MASTER_TCP_FD;
        }
        
        return PROBLEM_UDP_FD;
    }

    /* init all the tcp fd's*/
    for (i = 0; i < MAX_CLIENTS; i++)
    {
        client_socket[i] = -1;
    }

    /*set stdin as nonblocking*/
    if(fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK) < 0)
	{
		return -1;
	}
	
	/*set stdout as nonblocking*/
	if(fcntl(STDOUT_FILENO, F_SETFL, O_NONBLOCK) < 0)
	{
		return -1;
	}


    while (1)
    {

        timeout.tv_sec = 7;

        FD_ZERO(&rset);                            /* clears all the fd's. because select within loop, the sets must be reinitialized  before each  call*/
        FD_SET(udp_fd, &rset);
        FD_SET(tcp_fd, &rset);
        FD_SET(STDIN_FILENO, &rset);

        maxfd = udp_fd > tcp_fd ? udp_fd : tcp_fd;              /* needed for select function */

        for (i = 0; i < MAX_CLIENTS; i++)                       /* keep polling for I/O operations */
        {
            sd = client_socket[i];
            if (0 < sd)
            {
                FD_SET(sd, &rset);                              /* if found, set it in the select readfds set*/
            }
            if (sd > maxfd)
            {
                maxfd = sd;
            }
        }

        num_fds = select(maxfd + 1, &rset, NULL, NULL, &timeout); /* select should return the number of fd's in the sets */

        if (0 == num_fds)
        {
            LogtoFile("nothing happens for 7 seconds");          /* reval 0 means timeout expired before any file descriptors became ready */
        }

        if (-1 == num_fds)
        {
            return errno;
        }

        if (FD_ISSET(tcp_fd, &rset))                            /* check if the master tcp file descriptor is still present in the set */
        {

            client_fd = AcceptNewFD(tcp_fd, &tcp_src_address); /* accept the new connection in a new fd   */

            for (i = 0; i < MAX_CLIENTS; i++)                   /* find a free element in the clients array and assign the new fd there */
            {
                if (client_socket[i] == -1)
                {
                    client_socket[i] = client_fd;
                    printf("Adding to list of sockets as %d\n", i);
                    break;
                }
            }
        }
        
        for (i = 0; i < MAX_CLIENTS; i++)                       /* check if there is a fd in the set and ready */
        {
            sd = client_socket[i];
            if (FD_ISSET(sd, &rset))
            {
                recieve_retval = TcpRecieveMessage(sd, tcp_message_to_read, BUFFER_SIZE);  /* recv  */
                
                if (0 == recieve_retval)                        /* 0 means connection died */
                {
                    printf("connnection died\n");
                    LogtoFile("tcp connect closed\n");
                    if (0 != close(sd))
                    {
                        return -1;
                    }
                    client_socket[i] = -1;
                    FD_CLR(sd, &rset);
                    continue;
                }

                if (0 > recieve_retval)
                {
                    printf("error recieving message\n");
                    return -1;
                }
               
                tcp_message_to_read[strlen(tcp_message_to_read)] = '\0';

                printf("server recieved message from TCP : %s\n", tcp_message_to_read);

                CheckMessage(tcp_message_to_read,message_to_send);  /* check the message and set answer accordingly */
                
                if (-1 == TcpSendMessage(sd, message_to_send, BUFFER_SIZE))  /* send */
                {
                    printf("error sendind message\n");
                    if (0 != close(sd))
                    {
                        return -1;
                    }
                    client_socket[i] = -1;
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

            stdin_message_to_read[strlen(stdin_message_to_read)-1] = '\0';
            printf("recieved: %s\n", stdin_message_to_read);

            if (1 == CheckMessage(stdin_message_to_read,message_to_send))           /* check if client sent 'quit', or if not set proper answer */
            {
                printf("exit now..\n");
                return Destroy(tcp_fd,udp_fd,client_socket);                           /* close all the opened fd's*/
            }

            if (-1 == StdinResponse(STDIN_FILENO, message_to_send, strlen(message_to_send))) 
            {
                    return -1;
            }
            memset(stdin_message_to_read, '\0', BUFFER_SIZE);
        }
        if (FD_ISSET(udp_fd, &rset))
        {

            if (0 != UdpGetMessage(udp_fd, udp_message_to_read, BUFFER_SIZE, &udp_src_address)) /* read from stdin */
            {
                return errno;
            }

            CheckMessage(udp_message_to_read,message_to_send);              /* check the message and set answer accordingly */

            if (-1 == UdpResponse(udp_fd, message_to_send, strlen(message_to_send) + 1, &udp_src_address))
            {
                return -1;
            }
            memset(udp_message_to_read, '\0', BUFFER_SIZE);
            
        }

    }
    return 0;
}

int CheckMessage(char *message_to_read, char* message_to_send)
{

    if (0 == strcmp(message_to_read, "quit"))
    {
        return 1;
    }

    if (0 == strcmp(message_to_read, "ping"))
    {
        memcpy(message_to_send,"pong\n",5);
        message_to_send[5] = '\0';
        return 0;
    }
    memcpy(message_to_send,"gever you need to send ping\n",28);
    return -1;
}

int Destroy(int tcp_fd,int udp_fd,int *client_socket)
{
    int i = 0;
    int result = 0;
    if (0 != close(tcp_fd) && errno != EBADF) /* verify that the fd is valid */
    {
        result = PROBLEM_MASTER_TCP_FD;
    }

    if (0 != close(udp_fd) && errno != EBADF) /* verify that the fd is valid */
    {
        result = PROBLEM_UDP_FD;
    }

    for (i = 0; i < MAX_CLIENTS; i++)
    {
        if (0 != close(client_socket[i]) && errno != EBADF) /* verify that the fd is valid */
        {
            result = PROBLEM_REGULAR_TCP_FD;
        }
    }
    
    return  result;
}
