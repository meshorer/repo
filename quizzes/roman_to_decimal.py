
def from_roman_to_decimal(num):
    values = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
    total = 0
    for i in range(len(num)):
        # If the current value is greater than the previous value, subtract twice the previous value
        if i > 0 and values[num[i]] > values[num[i - 1]]:
            total += values[num[i]] - 2 * values[num[i - 1]]
        else:
            # Otherwise, add the current value to the total
            total += values[num[i]]
    return total

print(from_roman_to_decimal("IV"))
print(from_roman_to_decimal("MMDXVIII"))