/* 
    Create socket with socket() call
    bind() this to an IP and port where it can
    listen() for connections, then
    accept() connection 
    and send() or receive() data to/from connected sockets

*/

#include <sys/socket.h>
#include <netinet/in.h>   /*sockaddr_in */
#include <errno.h>
#include <stdio.h> /* sscanf*/
#include <unistd.h> /*read, write, close*/
#include <string.h> /* memsset*/


#define PORT 8000
#define BACKLOG 10
#define BUFFER_SIZE 1024

int main()
{
    int server_fd = 0;
    int client_fd = 0;
    struct sockaddr_in adddress = {0};
    ssize_t value_read = 0;
    char buffer[BUFFER_SIZE] = {0};
    char *hello = "hello world";
    int addrlen = sizeof(adddress);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        return -1;
    }
    
    adddress.sin_family = AF_INET;
    adddress.sin_addr.s_addr = INADDR_ANY;
    adddress.sin_port = htons(PORT);

    memset(adddress.sin_zero, '\0',sizeof(adddress.sin_zero));

    if (-1 == bind(server_fd,(struct sockaddr *)&adddress,sizeof(adddress)))  /* assigns  the
       address  specified  by  addr  to the socket referred to by the file de‐
       scriptor*/
    {
        return errno;
    } 

    printf("socket successfully bound to address\n");

    if (-1 == listen(server_fd,BACKLOG)) /* backlog defines how many pending connections will be queued up before it will be refused.*/
    {
        return errno;
    }

    printf("server listening for connections\n");

    while (1)
    {
        client_fd = accept(server_fd,(struct sockaddr *)&adddress,(socklen_t*)&addrlen);
        if (-1 == client_fd)
        {
            printf("failed to accept\n");
            return errno;
        }
        printf("im here\n");
        value_read = read(client_fd,buffer,BUFFER_SIZE);
        if (-1 == value_read)
        {
            return errno;
        }
        printf("message is: %s\n",buffer);
        write(client_fd,hello,strlen(hello));

        close(client_fd);        

    }
    
    return 0;
}