# ​Create a lambda function that receives two arguments and adds them.

def add_them(a,b):
    return (lambda x,y: x+y)(a,b)

print(add_them("1","2"))