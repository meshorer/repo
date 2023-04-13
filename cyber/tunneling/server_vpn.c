#include <stdio.h>
#include <stdlib.h> /* system */
#include <string.h> /* memset, strncpy */
#include <unistd.h> /* close, read, write */
/*#include <sys/socket.h> 
#include <sys/types.h> 
#include <sys/stat.h> */
#include <sys/ioctl.h> /* ioctl */
#include <fcntl.h>  /* open */
#include <linux/if.h> /* ifr, IFNAMSIZ */
#include <linux/if_tun.h> /* IFF_TUN; ,TUNSETIFF */
#include <sys/select.h> /* select*/
#include <arpa/inet.h> /* inet_addr*/


#define MTU 1400
#define PORT 1777



int tun_alloc(char *dev)
{
    struct ifreq ifr;
    int fd = 0, err = 0;

    if ((fd = open("/dev/net/tun", O_RDWR)) < 0)
    {
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    ifr.ifr_flags = IFF_TUN;
    if (*dev)
    {
        printf("dev is exist\n");
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0)
    {
        close(fd);
        return err;
    }
    printf("tun alloc worked\n");
    return fd;
}

/*
 * Configure IP address and MTU of VPN interface /dev/tun0
 */
int ifconfig()
{
    char cmd[1024];

    sprintf(cmd,  "ifconfig tun0 10.8.0.1/24 mtu %d up", MTU);
    if (-1 == system(cmd))
    {
        return -1;
    }
    return 0;
}

void setup_route_table()
{
  system("sysctl -w net.ipv4.ip_forward=1");

  system("iptables -t nat -A POSTROUTING -s 10.8.0.0/16 ! -d 10.8.0.0/16 -m comment --comment 'vpndemo' -j MASQUERADE");
  system("iptables -A FORWARD -s 10.8.0.0/16 -m state --state RELATED,ESTABLISHED -j ACCEPT");
  system("iptables -A FORWARD -d 10.8.0.0/16 -j ACCEPT");
}


void cleanup_route_table()
{
    system("iptables -t nat -D POSTROUTING -s 10.8.0.0/16 ! -d 10.8.0.0/16 -m comment --comment 'vpndemo' -j MASQUERADE");
    system("iptables -D FORWARD -s 10.8.0.0/16 -m state --state RELATED,ESTABLISHED -j ACCEPT");
    system("iptables -D FORWARD -d 10.8.0.0/16 -j ACCEPT");
}




int TcpCreateSocket(int port, struct sockaddr_in *address)
{
    int fd = 0;
    int flags = 0;
    socklen_t addrlen = 0;
    /int opt = 1;/

    addrlen = sizeof(struct sockaddr_in);#include <stdio.h>
#include <stdlib.h> /* system */
#include <string.h> /* memset, strncpy */
#include <unistd.h> /* close, read, write */
/*#include <sys/socket.h> 
#include <sys/types.h> 
#include <sys/stat.h> */
#include <sys/ioctl.h> /* ioctl */
#include <fcntl.h>  /* open */
#include <linux/if.h> /* ifr, IFNAMSIZ */
#include <linux/if_tun.h> /* IFF_TUN; ,TUNSETIFF */
#include <sys/select.h> /* select*/
#include <arpa/inet.h> /* inet_addr*/


#define MTU 1400
#define PORT 1777



int tun_alloc(char *dev)
{
    struct ifreq ifr;
    int fd = 0, err = 0;

    if ((fd = open("/dev/net/tun", O_RDWR)) < 0)
    {
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    ifr.ifr_flags = IFF_TUN;
    if (*dev)
    {
        printf("dev is exist\n");
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0)
    {
        close(fd);
        return err;
    }
    printf("tun alloc worked\n");
    return fd;
}

/*
 * Configure IP address and MTU of VPN interface /dev/tun0
 */
int ifconfig()
{
    char cmd[1024];

    sprintf(cmd,  "ifconfig tun0 10.8.0.1/24 mtu %d up", MTU);
    if (-1 == system(cmd))
    {
        return -1;
    }
    return 0;
}

void setup_route_table()
{
  system("sysctl -w net.ipv4.ip_forward=1");

  system("iptables -t nat -A POSTROUTING -s 10.8.0.0/16 ! -d 10.8.0.0/16 -m comment --comment 'vpndemo' -j MASQUERADE");
  system("iptables -A FORWARD -s 10.8.0.0/16 -m state --state RELATED,ESTABLISHED -j ACCEPT");
  system("iptables -A FORWARD -d 10.8.0.0/16 -j ACCEPT");
}


void cleanup_route_table()
{
    system("iptables -t nat -D POSTROUTING -s 10.8.0.0/16 ! -d 10.8.0.0/16 -m comment --comment 'vpndemo' -j MASQUERADE");
    system("iptables -D FORWARD -s 10.8.0.0/16 -m state --state RELATED,ESTABLISHED -j ACCEPT");
    system("iptables -D FORWARD -d 10.8.0.0/16 -j ACCEPT");
}




int TcpCreateSocket(int port, struct sockaddr_in *address)
{
    int fd = 0;
    socklen_t addrlen = 0;
    int opt = 1;

    addrlen = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        return -1;
    }
     printf("socket worked\n");
    /*if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        printf("setsockopt failed\n");
    }*/

    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_addr.s_addr =INADDR_ANY;

    if (-1 == bind(fd,(struct sockaddr *)address,addrlen))
    {
        return -1;
    } 
     printf("bind worked\n");
    if (-1 == listen(fd,1)) /* backlog defines how many pending connections will be queued up before it will be refused.*/
    {
        return -1;
    }
     printf("listen worked\n");

    return fd;
}


int AcceptNewFD(int fd,struct sockaddr_in *src_address)
{
    int client_fd = 0;
    socklen_t addrlen = 0;
    addrlen = sizeof(struct sockaddr_in);

    client_fd = accept(fd,(struct sockaddr *)src_address,&addrlen);
    
    if (client_fd < 0)
    {
        printf("Failed to accept\n");
        return -1;
    }

    return client_fd;
}


 int main()
{
    struct sockaddr_in socket_address = {0};
    struct sockaddr_in tcp_src_address = {0};
    int tcp_fd = 0;
    int tun_fd = 0;
    int client_fd = 0;
    int maxfd = 0;
    int num_fds = 0;
    fd_set rset = {0};
    int recieve_retval = 0;
    int send_value = 0;

    /*
   * tun_buf - memory buffer read from/write to tun dev - is always plain
   * tcp_buf - memory buffer read from/write to udp fd - is always encrypted
   */
    char tun_buf[MTU] = {0};
    char tcp_buf[MTU] = {0};

    tcp_fd = TcpCreateSocket(PORT, &socket_address);
    if (0 > tcp_fd)
    {
        return -1;
    }

    client_fd = AcceptNewFD(tcp_fd, &tcp_src_address);
    if (-1 == client_fd)
    {
        return -1;
    }
    printf("accept worked\n");

    if ((tun_fd = tun_alloc("tun0")) < 0)
    {
        return -1;
    }

    ifconfig();
    setup_route_table();
    
    while (1)
    {
        FD_ZERO(&rset);                            /* clears all the fd's. because select within loop, the sets must be reinitialized  before each  call*/
        FD_SET(client_fd, &rset);
        FD_SET(tun_fd, &rset);

        maxfd = client_fd > tun_fd ? tcp_fd : tun_fd;

        num_fds = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (-1 == num_fds)
        {
            return -1;
        }

        if (FD_ISSET(tun_fd, &rset))
        {
            recieve_retval = read(tun_fd,tun_buf,MTU);
            if (recieve_retval < 0)
            {
                printf("problem with read\n");
                break;
            }

            send_value = write(tcp_fd,tun_buf,recieve_retval);
            if (send_value < 0)
            {
                printf("problem with write\n");
                break;
            }
            memset(tun_buf, 0, MTU);
        }

        if (FD_ISSET(client_fd, &rset))
        {
            recieve_retval = read(tcp_fd,tcp_buf,MTU);
            if (recieve_retval < 0)
            {
                printf("problem with recieve\n");
                break;
            }

            send_value = write(tun_fd,tcp_buf,recieve_retval);
            if (send_value < 0)
            {
                printf("problem with write\n");
                break;
            }
            memset(tcp_buf, 0, MTU);
        }   

    }

    close(tcp_fd);
    close(tun_fd);
    cleanup_route_table();
    return 0;
}

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        return -1;
    }
     printf("socket worked\n");
    /*if( setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        printf("setsockopt failed\n");
    }*/

    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_addr.s_addr =INADDR_ANY;

    if (-1 == bind(fd,(struct sockaddr *)address,addrlen))
    {
        return -1;
    } 
     printf("bind worked\n");

    /*flags = fcntl(fd, F_GETFL, 0);
    if (flags != -1)
    {
        if (-1 == fcntl(fd, F_SETFL, flags | O_NONBLOCK))
        {
            printf("problem with fcntl\n");
        }
    }*/

    if (-1 == listen(fd,1)) /* backlog defines how many pending connections will be queued up before it will be refused.*/
    {
        return -1;
    }
     printf("listen worked\n");

    return fd;
}


int AcceptNewFD(int fd,struct sockaddr_in *src_address)
{
    int client_fd = 0;
    socklen_t addrlen = 0;
    addrlen = sizeof(struct sockaddr_in);

    client_fd = accept(fd,(struct sockaddr *)src_address,&addrlen);
    
    if (client_fd < 0)
    {
        printf("Failed to accept\n");
        return -1;
    }

    return client_fd;
}


 int main()
{
    struct sockaddr_in socket_address = {0};
    struct sockaddr_in tcp_src_address = {0};
    int tcp_fd = 0;
    int tun_fd = 0;
    int client_fd = 0;
    int maxfd = 0;
    int num_fds = 0;
    fd_set rset = {0};
    int recieve_retval = 0;
    int send_value = 0;

    /*
   * tun_buf - memory buffer read from/write to tun dev - is always plain
   * tcp_buf - memory buffer read from/write to udp fd - is always encrypted
   */
    char tun_buf[MTU] = {0};
    char tcp_buf[MTU] = {0};

    tcp_fd = TcpCreateSocket(PORT, &socket_address);
    if (0 > tcp_fd)
    {
        return -1;
    }

    client_fd = AcceptNewFD(tcp_fd, &tcp_src_address);
    if (-1 == client_fd)
    {
        return -1;
    }
    printf("accept worked\n");

    if ((tun_fd = tun_alloc("tun0")) < 0)
    {
        return -1;
    }

    ifconfig();
    setup_route_table();
    printf("enter to while\n");
    while (1)
    {
        FD_ZERO(&rset);                            /* clears all the fd's. because select within loop, the sets must be reinitialized  before each  call*/
        FD_SET(client_fd, &rset);
        FD_SET(tun_fd, &rset);

        maxfd = client_fd > tun_fd ? client_fd : tun_fd;

        num_fds = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (-1 == num_fds)
        {
            return -1;
        }

        if (FD_ISSET(tun_fd, &rset))
        {
            printf("in isset tun\n");
            recieve_retval = read(tun_fd,tun_buf,MTU);
            printf("just read from tun\n");
            if (recieve_retval < 0)
            {
                printf("problem with read\n");
                break;
            }
            printf("read %d bytes\n",recieve_retval);
            send_value = write(client_fd,tun_buf,recieve_retval);
            printf("just write to socket\n");
            if (send_value < 0)
            {
                printf("problem with write\n");
                break;
            }
            memset(tun_buf, 0, MTU);
        }

        if (FD_ISSET(problem with writeclient_fd, &rset))
        {
            printf("in isset tcp\n");
            recieve_retval = read(client_fd,tcp_buf,MTU);
            if (recieve_retval < 0)
            {
                printf("problem with recieve\n");
                break;
            }

            send_value = write(tun_fd,tcp_buf,recieve_retval);
            if (send_value < 0)
            {
                printf("problem with write\n");
                break;
            }
            memset(tcp_buf, 0, MTU);
        }   

    }

    close(tcp_fd);
    close(tun_fd);
    close(client_fd);
    cleanup_route_table();
    return 0;
}