
def count_letters(string):
    my_dict = {}
    for letter in string:
        if letter in my_dict:
            my_dict[letter] += 1
        else:
            my_dict[letter] = 1
    return my_dict
print(count_letters("dani man"))

def count_letters_no_if(string):
    my_dict = {}
    for letter in string:
        count = my_dict.get(letter, 0)
        my_dict[letter] = count + 1
    return my_dict
print(count_letters_no_if("dani man"))

def count_letters_using_dict(string):
    my_dict = dict.fromkeys(string, 0)
    for letter in string:
        my_dict[letter] = string.count(letter)
    return my_dict
print(count_letters_using_dict("dani man"))


def make_dictionary_using_yahav(string):
    dictionary = {}
    for letter in string:
        dictionary[letter] = dictionary.get(letter, 0) + 1
    return dictionary
print(make_dictionary_using_yahav("dani man"))

def ex4_list(my_list):
    return list(enumerate(my_list))
a = ['a','b',3]
print(ex4_list(a))


def ex4_dict2(my_list):
    return dict(enumerate(my_list.items()))
a = {"a": 1, "b": 2}
print(ex4_dict2(a))

# Create a function that receives 2 lists and 
# returns a list containing only the elements that are in 
# both lists.

a = [1,2,3,4]
b = [5,6,1,8,3]

def ex5_1(list1, list2):
    list3 = []
    for i in list1:
        if i in list2:
                list3.append(i)
    return list3
print(ex5_1(a,b))


def ex5_2(list1, list2):
    return list(filter(lambda x: x in list1, list2))
print(ex5_2(a,b))

def ex5_3(list1, list2):
    return [element for element in list1 if element in list2]
print(ex5_3(a,b))


def ex5_4(list1, list2):
    return list(set(list1).intersection(list2))
print(ex5_4(a,b))

def common_elements(list1, list2):
    return [element for element in list1 if (lambda x: x in list2)(element)]
print(common_elements(a,b))

def left_rotate(lst, n):
    return lst[n:] + lst[:n] # cut the n elements of the list, and add them at the end of the list
a = [1,2,3,4,5,6]
print(left_rotate(a,1))

if __name__ == '__main__':
    print("works only whem this module is not imported")


