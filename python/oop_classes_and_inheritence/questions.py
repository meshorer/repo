class what_f(object):
    def __init__(self,a,b):
        
        self.a = a
        self.b = b
    def something(self):
        self.j = 6666
        self.k = 10101

x = what_f(1, 2)
x.z = 42  # what is happening here?
print(x.a)

print(getattr(x,'z'))
x.something()
print(x.j)
class B(object):
    def foo(self):
        return "B"

class D(B):
    def foo(self):
        return "C"

b = B()
d = D()
print (b.foo())
print (d.foo())
z = D()
z.new = 3
print(getattr(z,'new'))
print(isinstance(b,(D,B)))
print(isinstance(3,(int)))


