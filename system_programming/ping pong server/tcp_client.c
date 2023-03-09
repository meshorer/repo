#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int main(void)
{
    int socket_desc = 0;
    struct sockaddr_in server_addr;
    char server_message[2000] = {0};
    char client_message[2000] = {0};
    int num_pings = 0;
    int seconds = 0;
    int i = 0;
    int recieve_value = 0;
    int send_value = 0;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
    
    printf("Socket created successfully\n");
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1777);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        return -1;
    }
                          
    srand(time(0));
    num_pings = rand() % (10 - 3 +1) +3;
    printf("num ping is: %d\n", num_pings);
    for (i = 0; i < num_pings; i++)
    {
        printf("Enter message: \n");
        gets(client_message);
        
        send_value = send(socket_desc, client_message, strlen(client_message), 0);
        
        if(send_value < 0)
        {
            printf("Unable to send message\n");
            return -1;
        }
        
        recieve_value = recv(socket_desc, server_message, sizeof(server_message), 0);

        printf("recieve_value %d\n",recieve_value);

        if( recieve_value < 0)
        {
            printf("Error while receiving server's msg\n");
            return -1;
        }
        else if (0 == recieve_value)
        {
            printf("no connection\n");
            close(socket_desc);
            return -1;
        }
        
        printf("Server's response: %s\n",server_message);
    }
    close(socket_desc);
    
    return 0;
}
