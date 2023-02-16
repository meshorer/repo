def left_rotate(lst, n):
    return lst[n:] + lst[:n] # cut the n elements of the list, and add them at the end of the list
a = [1,2,3,4,5,6]
print(left_rotate(a,1))
print(locals())