def hello_func(*args, **kwargs):
    if  "name" in kwargs:
        print(kwargs.get("name"))
    else:
        print("no name was passed")
hello_func("1,2,dani",name="hello", me="dada")


