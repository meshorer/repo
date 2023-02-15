
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

def IntToAsci():
	my_int = 48
	my_str = chr(my_int)
	print(my_str)
IntToAsci()

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


def IsLeapYear(year):
	if (year % 4 == 0 and year % 100 != 0 or year % 400 == 0):
		print("leap")
	else:
		print("not leap")
IsLeapYear(400)
		

def is_int(num):
	print(isinstance(num, int))
is_int(10.3)


def FlipInt(num):
	reverse_num = 0
	while num> 0:
    		
   	 	digit = num % 10 			# find the remainder - the last digit
    		
    		num = num // 10				# divide completely - remove the last digit
    		
    		reverse_num = reverse_num * 10		# increase the bit width of the second number
    		
    		reverse_num = reverse_num + digit  	# add another digit

	print ('The "inverse" number:', reverse_num)
FlipInt(123)









