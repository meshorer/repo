
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