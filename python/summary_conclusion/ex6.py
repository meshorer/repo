# When we make dir on a str we receive a list of all the available methods. Reduce the list to only the not dunder methods.

    # Do it with and without list comprehension
    # Advanced: use function filter

def no_list_comprehension(my_list):
    new_list = list(filter(lambda x: "__" not in x, my_list))
    return new_list



print(no_list_comprehension(dir(str)))
print()


#  newlist = [x for x in fruits if x != "apple"] 


def with_list_comprehension(my_list):
   return [x for x in my_list if "__" not in x]

print(with_list_comprehension(dir(str)))
