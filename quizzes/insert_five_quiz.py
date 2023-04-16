def insert_five(num):
    num = str(num)
    for digit in num:
        if int(digit) < 5:
            new_num = (num.replace(str(digit),'5'))
            return new_num
    return num

print(insert_five(648))