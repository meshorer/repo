
# question 7
def format_message1():

	name = "Alice"
	age = 30
	message = "My name is {} and I am {} years old" .format(name, age)
	print(message)
	
format_message1()


def format_message2():
	name = "Alice"
	age = 30
	message = f"My name is {name} and I will be {age+1} years old next year"
	print(message)
	
format_message2()

# question 13
def my_function(arg1, arg2, arg3):
	print(arg1, arg2, arg3)
   
my_function(arg3=3, arg1=1, arg2=2) # call the function with arguments in a different order


# question 14

def max_int():
	import sys
	maxi = sys.maxsize
	maxi-=1
	print(maxi)
	
max_int()

def int_to_asci():
	my_int = 48
	my_str = chr(my_int)
	print(my_str)
int_to_asci()

def is_even(num):
    if num % 2 == 0:
        print("even")
    else:
         print("odd")
is_even(5)

def StringCorrespondingInt(string, num):
	x = range(num)
	for i in x:
		print(string)
		
StringCorrespondingInt("daniel", 3)


def is_leap_year(year):
	if (year % 4 == 0 and year % 100 != 0 or year % 400 == 0):
		print("leap")
	else:
		print("not leap")
is_leap_year(400)
		

def is_int(num):
	print(isinstance(num, int))
is_int(10.3)


def flip_int(num):
	num = str(num)		# convert to string
	num = num[::-1]		# flip the string
	print(num)

flip_int(123.456)

def grades(num):
    if(num in range(0,10)):
        print('F')
    elif(num in range(10,30)):
        print('E')
    elif(num in range(30,50)):
        print('D')
    elif(num in range(50,70)):
        print('C')
    elif(num in range(70,90)):
        print('B')
    elif(num in range(90,101)):
        print('A')

grades(100)


def factorial(num):

	if num == 0:
		return 1
		
	return num * Factorial(num - 1)
print(Factorial(0))
	







