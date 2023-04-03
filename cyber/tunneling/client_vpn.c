#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#define MTU 1400
#define SERVER_HOST "10.8.0.4"

int tun_alloc(char *dev)
{
    struct ifreq ifr;
    int fd, err;

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
       strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0)
    {
        close(fd);
        return err;
    }
    return fd;
}

/*
 * Configure IP address and MTU of VPN interface /dev/tun0
 */
int ifconfig()
{
    char cmd[1024];

    snprintf(cmd, sizeof(cmd), "ifconfig tun0 10.8.0.2/24 mtu %d up", MTU);

    if (-1 == system(cmd))
    {
        return -1;
    }
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
    printf("line 72\n");
    system("iptables -I  1 -i tun0 -m state --state RELATED,ESTABLISHED -j ACCEPT");
    printf("line 74\n");
    system("iptables -I FORWARD 1 -o tun0 -j ACCEPT");
    snprintf(cmd, sizeof(cmd), "ip route add %s via $(ip route show 0/0 | sed -e 's/.* via \([^ ]*\).*/\1/')", SERVER_HOST);
    system(cmd);
    system("ip route add 0/1 dev tun0");
    system("ip route add 128/1 dev tun0");

    return 0;
}

int main()
{
    int tun_fd;
    if ((tun_fd = tun_alloc("tun0")) < 0)
    {
        return -1;
    }

    ifconfig();
    setup_route_table();

    return 0;
}