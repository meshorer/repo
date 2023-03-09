#ifndef __tcp_H__ILRD__CR3_

#define __tcp_H__ILRD__CR3_

#include <stddef.h> /* size_t*/

int TcpCreateSocket(int port, struct sockaddr_in *address);

int TcpGetMessage(int fd,struct sockaddr_in *src_address);

extern int CheckMessage(char *message_to_read);

int TcpRecieveMessage(int fd,void *message_to_read,size_t buflen);

int TcpSendMessage(int fd,void *message_to_send,size_t buflen);



#endif /* _tcp_H__ILRD__CR3_ */