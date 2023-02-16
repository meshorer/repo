# switch between two variables in one line
def switch_value(num1, num2):
    num1, num2 = num2, num1
    return num1, num2
print(switch_value(1, 2))


#question 3
print("Question 3")
def question_3():
    x = [1,2,3]
    y = x
    y[0] = 8
    print(x)
question_3()

#question 5
print("Question 5")
def question_5():
    x = 1
    y = x
    y = 2
    print(x)
question_5()

#question 7
print("Question 7")
def Question_7(n):
    n+=1
a = 555
Question_7(a)
print(a)


#question 8
print("Question 8")
def Question_8(ls):
    ls+=[1]
a = [4,3,2]
Question_8(a)
print(a)

#exercise 1

print("exercise 1")         # with size of list
squared = [0] * 11          # initialize the list to contain 13 elements
for i in range(11):
    squared[i] = i*i        # square the current number and assign it to the corresponding element in the list
print(squared)

       
squared = []                # without size of list
for i in range(11):
    squared.append(i*i)    


squared = [] 
i = 0
while 100 >= i * i:
     squared.append(i*i)
     i += 1  
print(squared)

