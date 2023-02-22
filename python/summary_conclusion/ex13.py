# Implement a generator that gives Infinite squared numbers (0, 1, 4, 9, 16, 25 ...)
import time

# num = 0
# while True:
#     print(num ** 2)
#     num += 1
#     time.sleep(1)

def infinite_sequence():
    num = 0
    while True:
        yield num ** 2
        num += 1
        time.sleep(1)

for i in infinite_sequence():
    print(i, end=", ", flush=True) # flush=True forces the output to be immediately written to the console
