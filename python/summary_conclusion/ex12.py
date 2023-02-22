# ​Implement a DefaultDict - it is similar to a dict but, it receives a default value at creation
# if a key does not exist when trying to access it in the DefaultDict, it will return the default value.


class DefaultDict(dict):

    def __init__(self,default_value):
        self.default_value = default_value

    def __setitem__(self, key, value):
        if not key in self:
            return self.default_value
        super().__setitem__(key, value)

d = DefaultDict(0)
d['a'] = "hello"
print(d['a'])
    