def is_even(number):
    try:
        return number % 2 == 0
    except TypeError:
        raise TypeError("number needs to be a number")

print(is_even(2))
print(is_even(3))
