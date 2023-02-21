try:
    1/b
except Exception:
    print( "some exception happened")
except ZeroDivisionError:
    print ("caught division by 0")
