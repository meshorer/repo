import socket

# Read the list of words from a file
with open('/usr/share/dict/american-english', 'r') as f:
    words = f.read().splitlines()

url = input("Enter a URL: ")

for word in words:
    subdomain = word + '.' + url

    # Get the IP address of the subdomain
    try:
        ip_address = socket.gethostbyname(subdomain)
        print(f"{subdomain} resolves to {ip_address}")
    except socket.gaierror:
        continue