# ​Create a function that receives a list and removes all the non str objects from it.


def remove_non_str(my_list):
    return [x for x in my_list if not isinstance(x, str)]

print(remove_non_str(["1",2,4]))

