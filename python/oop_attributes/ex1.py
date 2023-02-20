class X(object):
    def __init__(self, a):
        self.a = a
    def __getattr__(self, name):
        return f"attribute {name} doesn't exist"

my_class = X(7)
print (my_class.a)
print(X(1).a)
print(X(1).b)
