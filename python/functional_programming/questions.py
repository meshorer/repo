n = 3
def foo():
    n = 4
    def bar():
        print(n)
    bar() 

foo()

n = 3
def foo():
    n = 4
    def bar():
        print(n)
    return bar

f = foo()
f()



def fooother(**args):
    print(args)


a = 4
fooother(args=3,arg=4)