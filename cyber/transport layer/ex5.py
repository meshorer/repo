
import socket
import threading

# Define a function to scan for an open port on a given IP address
def scan_port(ip_address, port):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.settimeout(0.1)  # Set a timeout value in seconds
        result = s.connect_ex((ip_address, port))
        if result == 0:
            print(f"Port {port} is open on {ip_address}")

# Prompt the user for an IP address and a port number to scan
ip_address = input("Enter an IP address to scan: ")
port = int(input("Enter a port number to scan: "))

# Set up the network address and subnet mask for the /8 network
network_address = ".".join(ip_address.split(".")[:1]) + ".0.0.0"

# Loop over all possible host IP addresses in the network
for i in range(10, 255):
    for j in range(0, 255):
        for k in range(1, 255):
            host_ip = ".".join(network_address.split(".")[:1]) + "." + str(i) + "." + str(j) + "." + str(k)
            # Create a new thread to scan for an open port on the current host
            thread = threading.Thread(target=scan_port, args=(host_ip, port))
            thread.start()
