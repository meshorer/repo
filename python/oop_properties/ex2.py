# class Property(object):
#     def __get__(self):
#         return self


# class X(object):
#     def __init__(self, val):
#         self.__x = int(val)
#     @Property()
#     def x(self):
#         return self.__x
# print (X(0).x)

class Property:
    def __init__(self, fget=None):
        
        self.fget = fget            # Initialize the descriptor with a getter function.
        
        self.fset = None            # Initialize the descriptor with no setter function.

    def __get__(self, obj, objtype=None):
        # If the descriptor is accessed on a class rather than an instance,
        # return the descriptor itself.
        if obj is None:
            return self
       
        if self.fget is None:        # If the descriptor has a getter function, call it and return its value.
            raise AttributeError("unreadable attribute")
        return self.fget(obj)

    def __set__(self, obj, value):
       
        if self.fset is None:        # If the descriptor has no setter function, raise an AttributeError.
            raise AttributeError("can't set attribute")
        
        self.fset(obj, value)        # Otherwise, call the setter function with the object and value.

    def Setter(self, fset):
        # Set the descriptor's setter function to the given function.
        self.fset = fset
        # Return the descriptor, so that it can be used as a decorator.
        return self

class X:
    def __init__(self, val):
        self.__x = int(val)

    @Property
    def x(self):
        return self.__x

    @x.Setter
    def x(self, val):
        self.__x = int(val)
a = X(0)
print (a.x)

a.x = 1
print (a.x)
