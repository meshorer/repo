#​Create a lambda function that receives one argument and squares it.

def square_it(arg):
   return (lambda x: x**2)(arg)
    
print(square_it(4))
