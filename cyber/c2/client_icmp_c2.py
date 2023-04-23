import os
from scapy.all import *

def pkt_send(source,dest,data):
    conf.L3socket = L3RawSocket
    sendp(IP(src=source,dst=dest)/ICMP()/data)

def sniff_pkt():
    capture = sniff(filter="icmp or icmp[0]=8",count=1,prn=parse_packet)
    print(capture)

def parse_packet(packet):
    if Raw in packet:
        data_recieved = packet[Raw].load
    print(data_recieved)

while 1:  
    pkt_send("127.0.0.1","127.0.0.1","check data")
    
 