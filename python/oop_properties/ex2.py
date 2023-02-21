class Property:
    def __init__(self, fget=None):
        # Initialize the descriptor with a getter function.
        self.fget = fget
        # Initialize the descriptor with no setter or deleter function.
        self.fset = None
        self.fdel = None

    def __get__(self, obj, objtype=None):
        # If the descriptor is accessed on a class rather than an instance,
        # return the descriptor itself.
        if obj is None:
            return self
        # If the descriptor has a getter function, call it and return its value.
        if self.fget is None:
            raise AttributeError("unreadable attribute")
        return self.fget(obj)

    def __set__(self, obj, value):
        # If the descriptor has no setter function, raise an AttributeError.
        if self.fset is None:
            raise AttributeError("can't set attribute")
        # Otherwise, call the setter function with the object and value.
        self.fset(obj, value)

    def __delete__(self, obj):
        # If the descriptor has no deleter function, raise an AttributeError.
        if self.fdel is None:
            raise AttributeError("can't delete attribute")
        # Otherwise, call the deleter function with the object.
        self.fdel(obj)

    def Setter(self, fset):
        # Set the descriptor's setter function to the given function.
        self.fset = fset
        # Return the descriptor, so that it can be used as a decorator.
        return self

    def Deleter(self, fdel):
        # Set the descriptor's deleter function to the given function.
        self.fdel = fdel
        # Return the descriptor, so that it can be used as a decorator.
        return self


class X:
    def __init__(self, x):
        self._x = x

    @Property
    def x(self):
        return self._x

    @x.Setter
    def x(self, value):
        self._x = value

    @x.Deleter
    def x(self):
        del self._x


a = X(0)
print(a.x)
a.x = 1
print(a.x)
del a.x