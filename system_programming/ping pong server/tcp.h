#ifndef __tcp_H__ILRD__CR3_

#define __tcp_H__ILRD__CR3_

#include <stddef.h> /* size_t*/

int TcpCreateSocket(int port, struct sockaddr_in *address);

int TcpGetMessage(int fd,void *buffer,size_t buflen,struct sockaddr_in *src_address);

int TcpResponse(int fd,const void *message,size_t message_len);


#endif /* _tcp_H__ILRD__CR3_ */