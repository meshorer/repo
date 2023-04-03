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
#define SERVER_HOST "10.8.0.4"

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

    sprintf(cmd,  "ifconfig tun0 10.8.0.2/24 mtu %d up", MTU);
    if (-1 == system(cmd))
    {
        return -1;
    }
    return 0;
}

/*
 * Setup route table via `iptables` & `ip route`
 */
int setup_route_table()
{
    char cmd[1024];
    printf("start setup_routing_table\n");
    system("sysctl -w net.ipv4.ip_forward=1");
    system("iptables -t nat -A POSTROUTING -o tun0 -j MASQUERADE");
    system("iptables -I FORWARD 1 -i tun0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
    printf("line 78\n");
    system("iptables -I FORWARD 1 -o tun0 -j ACCEPT");
    sprintf(cmd,"ip route add %s via $(route -n | grep 'UG[ \t]' | awk '{print $2}')", SERVER_HOST);
    printf("line 80\n");
    system(cmd);
    printf("line 82\n");
    system("ip route add 0/1 dev tun0");
    system("ip route add 128/1 dev tun0");  /*  this ensures that all traffic is captured via the virtual interface */

    return 0;
}


int tcp_connect()
{
    int socket_desc = 0;
    struct sockaddr_in server_addr;

    /*socklen_t val = 1;
    socklen_t valen = sizeof(val);*/

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
    
    printf("Socket created successfully\n");
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1777);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_HOST);
    
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        return -1;
    }
    return socket_desc;
}

void cleanup_route_table() {
  char cmd[1024] = {0};
  system("iptables -t nat -D POSTROUTING -o tun0 -j MASQUERADE");
  system("iptables -D FORWARD -i tun0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
  system("iptables -D FORWARD -o tun0 -j ACCEPT");
  sprintf(cmd, "ip route del %s", SERVER_HOST);
  system(cmd);
  system("ip route del 0/1");
  system("ip route del 128/1");
}

int main()
{
    int tcp_fd = 0;
    int tun_fd = 0;
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

    cleanup_route_table();
    if ((tun_fd = tun_alloc("tun0")) < 0)
    {
        return -1;
    }

    ifconfig();
    setup_route_table();
    tcp_fd = tcp_connect();
    while (1)
    {
        FD_ZERO(&rset);                            /* clears all the fd's. because select within loop, the sets must be reinitialized  before each  call*/
        FD_SET(tcp_fd, &rset);
        FD_SET(tun_fd, &rset);

        maxfd = tcp_fd > tun_fd ? tcp_fd : tun_fd;

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
        }

        if (FD_ISSET(tcp_fd, &rset))
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
        }   

    }

    close(tcp_fd);
    close(tun_fd);
    cleanup_route_table();
    return 0;
}