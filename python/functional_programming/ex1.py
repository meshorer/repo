from functools import reduce


def sum_for(my_list):
    sum = 0
    for i in my_list:
        sum+=i
    return sum
   
print(sum_for((1,3,5,7)))

def sum_with_reduce(my_list):
    
    return reduce(lambda x , i: x + i, my_list)
    
   
print(sum_with_reduce((1,3,5,7)))

def sum_with_sum(my_list):
    
    return sum(my_list)
print(sum_with_sum((1,3,5,7)))


