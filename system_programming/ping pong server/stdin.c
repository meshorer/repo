#include <stddef.h>
#include <unistd.h>

#include "stdin.h"

int StdinGetMessage(int fd,void *buffer,size_t bufflen)
{
    if (-1 == read(fd,buffer,bufflen))
    {
        return -1;
    }
    
    return 0;
}


int StdinResponse(int fd,const void *message,size_t message_len)
{
   
    if (-1 == write(fd,message,message_len))
    {
        return -1;
    }

    return 0;
}