
def div(a,b):
    if not isinstance(a, (int, float)) or not isinstance(b, (int, float)):
        raise TypeError("hey you can't do that")
    try:
        return a/b
    except ZeroDivisionError:
        return "tried to divide by zero"
    



    
print(div(1,0))
print(div(5,2))
print(div('a',2))

