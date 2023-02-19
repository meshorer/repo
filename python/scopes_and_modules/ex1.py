ok = 0
def check_if_in_globals(name):
    print(globals())
    return name in globals()


print(check_if_in_globals("ok"))

