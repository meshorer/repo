# ​Create a function that receives a list and returns a dict where values are the elements of the list, and key is their index.

#     Do it with and without dict comprehension

# >>> print(dict_from_list(['a', 'b', 'c']))
# {0: 'a', 1: 'b', 2: 'c'}

def no_dict_comprehension_dict_from_list(my_list):
    return dict(enumerate(my_list))

print(no_dict_comprehension_dict_from_list(['a', 'b', 'c']))

def with_dict_comprehension_dict_from_list(my_list):
    return {x:my_list[x] for x in range(len(my_list))}

print(with_dict_comprehension_dict_from_list(['a', 'b', 'c']))

