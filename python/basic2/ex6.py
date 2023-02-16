def left_rotate(lst, n):
    """
    Rotate the list `lst` to the left `n` times using slicing.

    Args:
    lst: A list to rotate.
    n: An integer indicating how many times to rotate the list.

    Returns:
    The rotated list.
    """
    return lst[n:] + lst[:n]
a = [1,2,3,4,5,6]
print(left_rotate(a,2))
