from cs50 import get_int
height = get_int("Height:")
width = height

if height >= 1 and height <= 8:

    for i in range(1, height + 1):
        num_hashes = i
        num_spaces = width - num_hashes
        #prints the hashes and spaces acording to the height inputed
        print(" " * num_spaces, end="")
        print("#" * num_hashes, end="")
        #creates the spaces between and the vertical structure
        print("  ", end="")
        print("#" * num_hashes)
else:
    height = get_int("Height:")
