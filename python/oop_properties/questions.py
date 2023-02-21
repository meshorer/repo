class X(object):
    """Example class"""
    def __init__(self):
        """init function for class X"""
        self.a = 1
        self._a = 2
        self.__a = 0
    
    def get_the_hidden_attribute(self):
        return (self.__a)

    def set_hidden_attribute(self,a):
        self.__a = a


x = X()
print(x.a)
print(x._a)
print(x.__dict__)
print(x.get_the_hidden_attribute())
x.set_hidden_attribute(10)
print(x.get_the_hidden_attribute())

print()
print()

class X(object):
    def __init__(self):
        self.__a = 1
    def get_a(self):
        print( "hello from get_a")
        return self.__a
    
    def set_a(self,a):
        print( "setter called")
        self.__a = a

    a = property(get_a,set_a)

x = X()
print(x.a)
x.a = 5
print(x.a)