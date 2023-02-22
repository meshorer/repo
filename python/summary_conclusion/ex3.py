#​Create a function that checks if a number is a prime number.

def is_prime(number):
    if number == 0 or number == 1:
        return False
        
    i = 2
    while i < number:
        if number % i == 0:
            return False
        i+=1
    return True

print(is_prime())