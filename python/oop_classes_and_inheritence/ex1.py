import numbers
import math

class Point(object):
    def __init__(self,x=0.0, y=0.0):
        self.x = x
        self.y = y

p = Point()
print(p.y)

class PointB(object):
    def __init__(self,x=0,y=0):
        if isinstance(x, numbers.Number) and isinstance(y, numbers.Number):
            self.x = x
            self.y = y 
        else:
            print("error")
            self.x = 0
            self.y = 0  

    def dist_from_origin(self):
        return (math.dist([self.x, self.y],[0,0]))

b = PointB(1,1)
print(b.y)
print(b.dist_from_origin())
