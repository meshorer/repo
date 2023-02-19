def seven_boom_for(num):
    a = []
    for i in range(num+1):
        if '7' in str(i) or i % 7 == 0:
            a.append(i)
    return a
        
print(seven_boom_for(17))


def seven_boom_list_comprehension(num):
    return [x for x in range(num+1) if x % 7 == 0 or '7' in str(x) ]
print(seven_boom_list_comprehension(17))


def seven_boomusing_map(num):
    a =  list(map(lambda x: (x) if x % 7 == 0 or '7' in str(x) else None , range(num+1)))    
    return list(filter(lambda x: x is not None, a))
print(seven_boomusing_map(17))
