#exercise 2
print("exercise 2")         # with size of list
even = []               
for i in range(101):
    if i % 2 == 0:
        even.append(i)
print(even)
print()
even = []
i = 0 
while 100 >= i:
    if i % 2 == 0:
        even.append(i)
    i+=1
print(even)
print()

even = []
i = 0 
even += range(0,101,2)
print(even)
