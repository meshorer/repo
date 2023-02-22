# ​Create a function that receives a list of numbers and increments them all.

from functools import reduce 

def increment_the_list(my_list):
   return reduce(lambda x,y: x + y, my_list)

print(increment_the_list([1,2,3]))