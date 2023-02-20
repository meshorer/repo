class  X(object):
    def __init__(self, a):
        object.__setattr__(self, 'a', a)

    def __setattr__(self, attr, value):
        if not hasattr(self, attr):
            raise AttributeError(f"attribute '{attr}' doesn't exist")
        object.__setattr__(self, attr, value)






my_class = X(4)
print(my_class.a)
my_class.a = 3
my_class.a = 5
print(my_class.a)

my_class.b = 8



#if attr not in self.__dict__:
#            raise AttributeError(f"attribute '{attr}' doesn't exist")

# object.__setattr__(self, attr, value)
