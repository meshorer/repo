def ex4_list(my_list):
    return list(enumerate(my_list))
a = ['a','b',3]
print(ex4_list(a))



def ex4_dict2(my_list):
    return dict(enumerate(my_list.items()))
print(ex4_dict2(a))