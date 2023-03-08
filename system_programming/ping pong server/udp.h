#ifndef __udp_H__ILRD__CR3_

#define __udp_H__ILRD__CR3_

#include <stddef.h> /* size_t*/

int UdpCreateSocket(int port, struct sockaddr_in *address);

int UdpGetMessage(int fd,void *buffer,size_t buflen,struct sockaddr_in *src_address);

int UdpResponse(int fd,const void *message,size_t message_len,const struct sockaddr_in *dest_address);


#endif /* _udp_H__ILRD__CR3_ */