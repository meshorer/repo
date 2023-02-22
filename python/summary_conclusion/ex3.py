#​Create a function that checks if a number is a prime number.

def is_prime(number):
    i = 2
    while i < number:
        if number%i == 0:
            return True
        i+=1
    return False

print(is_prime(11))