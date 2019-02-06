from cs50 import get_int
import sys

while True:

    cardno = get_int("Number: ")

    if cardno > 0:
        break

# Cast to a string for ease of use
cardno = str(cardno)

# Perform the length check
if len(cardno) not in (13, 15, 16):
    print("INVALID")
    sys.exit(0)

# Perform LUHN's algorithm
total_sum = 0
for idx, d in enumerate(reversed(cardno)):

    # Even digit
    # Multiply and add the digits of the product
    if (idx + 1) % 2 == 0:
        product = int(d) * 2
        for dgt in str(product):
            total_sum += int(dgt)
    # Odd digit
    # Just add
    else:
        total_sum += int(d)

# Check LUHN's algorithm output
if str(total_sum)[-1] != "0":
    print("INVALID")
    sys.exit(0)

# Now identify the card
if cardno[:2] in ("34", "37"):
    print("AMEX")
elif cardno[0] == "4":
    print("VISA")
elif int(cardno[:2]) >= 51 and int(cardno[:2]) <= 55:
    print("MASTERCARD")
else:
    print("INVALID")
