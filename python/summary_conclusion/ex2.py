import shutil
import os

def to_capital_content(path):

    secondfile_path = '/home/daniel/git/python/summary_conclusion/try.txt'
    with open(path,'r') as firstfile, open(secondfile_path,'w') as secondfile:
        for line in firstfile:
            secondfile.write(line.upper())
            
    shutil.copyfile(secondfile_path,path)

    if os.path.exists(secondfile_path):
        os.remove(secondfile_path)
    else:
        print("The file does not exist") 
    return path

to_capital_content("/home/daniel/git/python/summary_conclusion/test.txt")
