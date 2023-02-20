class Vehicle(object):
    __slots__ = ['model', 'manufacture']

    kind = 'car'

    def __init__(self, manufacture, model):
        self.manufacture = manufacture
        self.model = model
    def __repr__(self):
        return "<{manu}, {model}>".format(manu=self.manufacture, modle=self.model)

    def __getattr__(self, attr):
        return "attribute doesnt exist"

car = Vehicle("Toyota", "Corrola")

car.hey
print(getattr(car,'hey'))
print()
print(Vehicle.__dict__)
print()
print(car.__dict__)
print()
print(Vehicle.__mro__)