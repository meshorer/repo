def with_context_manager():
    path_to_path = input("enter path to file: ")
    with open(path_to_path, "r") as f:
        print(f.read().upper())

    

def without_context_manager():
    path_to_path = input("enter path to file: ")
    f = open(path_to_path, "r")
    try:
        print(f.read().upper())
    finally:
        f.close()
without_context_manager()

    