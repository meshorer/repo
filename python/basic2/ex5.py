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
