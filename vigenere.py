from sys import argv, exit
from cs50 import get_string

if len(argv) != 2:
    exit("Usage: python vigenere.py k")

k = argv[1]
if k.isalpha() is False:
    exit("Usage python vigenere.py k")

plaintext = get_string("plaintext: ")
output = ""

p_idx = 0
for c in plaintext:

    if c.isalpha() is False:
        output += c
        continue

    k_idx = p_idx % len(k)
    k_shift = ord(k[k_idx]) - ord('a') if k[k_idx].islower() \
        else ord(k[k_idx]) - ord('A')

    # The lower case
    if c.islower():
        new_c = ord('a') + ((ord(c) + k_shift) - ord('a')) % 26
        output += chr(new_c)

    # The upper case
    else:
        new_c = ord('A') + ((ord(c) + k_shift) - ord('A')) % 26
        output += chr(new_c)

    p_idx += 1

print(f"ciphertext: {output}")
