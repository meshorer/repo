# Create a function called make_adder which will return a 
# function that adds a number to the argument. Use a closure.

def make_adder(num):
    def increment(to_add):
        return num + to_add
    return increment

incer3 = make_adder(3)
print(incer3(3))

inc10 = make_adder(10)
print(inc10(10))