def ex2():
    return [x if x % 2 == 0 else "odd" for x in range(100)]
    
print(ex2())