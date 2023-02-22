# ​Implement a DefaultDict - it is similar to a dict but, it receives a default value at creation
# if a key does not exist when trying to access it in the DefaultDict, it will return the default value.


class DefaultDict(dict):

    def __init__(self,default_value):
        super().__init__()
        self.default_value = default_value

    def __getitem__(self, key):
        if not key in self:
            return self.default_value
        return super().__getitem__(key)
d = DefaultDict(0)
d['a'] = "hello"
print(d['b'])
    