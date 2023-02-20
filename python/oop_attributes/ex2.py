class  X(object):               # with __setattr__
    def __init__(self, a):
        object.__setattr__(self, 'a', a)   # this makes sure attribute a will be initialized despite __setattr__ method 

    def __setattr__(self, attr, value):
        if not hasattr(self, attr):
            raise AttributeError(f"attribute '{attr}' doesn't exist")
        object.__setattr__(self, attr, value)

my_class = X(4)
print(my_class.a)
my_class.a = 3
my_class.a = 5
print(my_class.a)



class Y(object):                    # with __slots__
    __slots__ = ['a']
    def __init__(self, a):
        self.a = a
my_class = Y(4)
print(my_class.a)
my_class.a = 3
my_class.a = 5
print(my_class.a)

my_class.b = 8
