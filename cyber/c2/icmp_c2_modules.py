import os
from scapy.all import *

def pkt_send(source,dest,data):
    sendp(IP(src=source,dst=dest)/ICMP()/data)

def sniff_pkt():
    capture = sniff(filter="icmp or icmp[0]=8",count=2,prn=parse_packet)
    print(capture)

def parse_packet(packet):
    print(packet.show())
  
#pkt_send("10.1.0.104","10.1.0.173","yarin_believe in us")
sniff_pkt()
    


