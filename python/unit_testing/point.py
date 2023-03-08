import numbers
import math

class CustomError(Exception):
    def __init__(self,x,y):
        self.x = x
        self.y = y
        value = 0
        if not isinstance(self.x, numbers.Number):
            value = self.x
        else:
            value = self.y
        self.message = f"you got an error,'{value}' is not a number dude, I make both x and y zero"
 

class Point(object):
    def __init__(self,x=0.0, y=0.0):
        self.x = x
        self.y = y
    
p = Point()

class PointB(object):
    def __init__(self,x=0,y=0):
        try:
            if isinstance(x, numbers.Number) and isinstance(y, numbers.Number):
                self.x = x
                self.y = y 
            else:
                raise CustomError(x,y)
        except CustomError as e:   # except to handle it so it will not fail the program
            print(e.message)
            self.x = 0.0
            self.y = 0.0 
            
        
            
    def dist_from_origin(self):
        return (math.dist([self.x, self.y],[0,0]))

b = PointB(7,"1")
print(b.x, b.y)
