
import socket

# Prompt the user for an IP address to scan
ip_address = input("Enter an IP address to scan: ")

# Loop over all possible port numbers and attempt a connection
for port in range(1, 65536):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:   # AF_INET - ipv4, SOCK_STREAM - means it is tcp  
        s.settimeout(0.1)  # Set a timeout value in seconds
        result = s.connect_ex((ip_address, port))

        # If the connection was successful, print the open port number
        if result == 0:
            print(f"Port {port} is open")