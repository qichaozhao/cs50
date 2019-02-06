from cs50 import get_int

while True:
    h = get_int("Height: ")

    if (h > 0 and h < 9):
        break

for i in range(1, h + 1):

    # Print whitespaces first
    for j in range(h - i):
        print(" ", end="")

    # Now print blocks
    for j in range(i):
        print("#", end="")

    # Print a newline
    print()