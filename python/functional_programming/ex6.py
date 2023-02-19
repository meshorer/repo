
def hello_func(*args, **kwargs):
    print(kwargs.get("name", "no name was passed")) # if there is no name passed then print "no name was passed"
hello_func("1,2,dani",name="hello", me="dada")

