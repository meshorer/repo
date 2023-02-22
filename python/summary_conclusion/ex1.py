import ntpath

def get_filename(path):
    return(ntpath.basename(path))


print(get_filename("a/b/c"))
