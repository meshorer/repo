#ifndef __STDIN_H__ILRD__CR3_

#define __STDIN_H__ILRD__CR3_

#include <stddef.h> /* size_t*/


int StdinGetMessage(int fd,void *buffer,size_t buflen);

int StdinResponse(int fd,const void *message,size_t message_len);


#endif /* _STDIN_H__ILRD__CR3_ */