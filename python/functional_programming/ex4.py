def list_to_dict_without_comprehension(my_list):
    return dict(enumerate(my_list))

print(list_to_dict_without_comprehension(["a", "b", "c"]))

def list_to_dict_comprehension(my_list):
        return {index:my_list[index] for index in range(len(my_list))}
print(list_to_dict_comprehension(["a", "b", "c"]))


