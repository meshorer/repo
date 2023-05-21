import string
import hashlib
import itertools
from timeit import default_timer as timer

to_run_on = string.ascii_lowercase + string.digits

def hash_create(algo,pass_clear):
    if 1 == algo:
        return hashlib.sha1(bytes(str(pass_clear),'utf-8')).hexdigest()
    elif 2 == algo:
        return hashlib.sha256(bytes(str(pass_clear),'utf-8')).hexdigest()
        
def brute_force(algo,pass_clear):
    global to_run_on
    actual_hash = hash_create(algo,pass_clear)
    attempts = 0
    start = timer()
    for password_length in range(1, 9):
        for guess in itertools.product(to_run_on, repeat=password_length):
            attempts += 1
            guess = ''.join(guess)
            hashed_guess = hash_create(algo,guess)
            if hashed_guess == actual_hash:
                end = timer()
                print("time: ",end - start)
                return 'password is {}. found in {} guesses.'.format(guess, attempts)
    return None
    
def main():
    ret_val = brute_force(2,"aaa2")
    if ret_val != None:
        print("password found")
        print(ret_val)
    else:
        print("not found")
        
if "__main__" == __name__:
    main()