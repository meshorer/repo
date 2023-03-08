#ifndef __tcp_H__ILRD__CR3_

#define __tcp_H__ILRD__CR3_

#include <stddef.h> /* size_t*/

int TcpCreateSocket(int port, struct sockaddr_in *address);

int TcpGetMessage(int fd,void *buffer,size_t buflen,struct sockaddr_in *src_address);

int TcpChat(int fd,void *message_to_read,void *message_to_send,size_t buflen);

extern int CheckMessage(char *message_to_read);


#endif /* _tcp_H__ILRD__CR3_ */