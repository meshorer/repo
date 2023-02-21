import numbers


class Point(object):
    """ i am a docstring hahaq"""
    def __init__(self):
        self._x = 0.0
        self._y = 0.0
    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, x):
        print("welcome to setter")
        if isinstance(x, numbers.Number):
            self._x = x
        else:
            print("error")
            self._x = 0.0

    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, y):
        print("welcome to setter")
        if isinstance(y, numbers.Number):
            self._y = y 
        else:
            print("error")
            self._y = 0.0

my_instance = Point()

my_instance.x = "dani"
print(my_instance.x)
my_instance.y = 4
print(my_instance.x,my_instance.y)
