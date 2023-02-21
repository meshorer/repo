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
        self.fget = fget
        self.fset = None

    def __get__(self, obj, objtype=None):
        if obj is None:
            return self
        if self.fget is None:
            raise AttributeError("unreadable attribute")
        return self.fget(obj)

    def __set__(self, obj, value):
        if self.fset is None:
            raise AttributeError("can't set attribute")
        self.fset(obj, value)

    def Setter(self, fset):
        self.fset = fset
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
