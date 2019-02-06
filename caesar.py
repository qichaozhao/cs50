from sys import argv, exit
from cs50 import get_string

if len(argv) != 2:
    exit("Usage: python caesar.py k")

k = int(argv[1])
plaintext = get_string("plaintext: ")
output = ""

for c in plaintext:

    # The lower case
    if c.islower():
        new_c = ord('a') + ((ord(c) + k) - ord('a')) % 26
        output += chr(new_c)

    # The upper case
    elif c.isupper():
        new_c = ord('A') + ((ord(c) + k) - ord('A')) % 26
        output += chr(new_c)

    # pass through any other char
    else:
        output += c

print(f"ciphertext: {output}")
