from cs50 import get_float

while True:

    change = get_float("Change owed: ")

    if (change > 0):
        break

#
# Define a function to help us find change
#


def find_change(chg, coins=[25, 10, 5, 1]):
    """
    chg should be in cents, not a floating point dollar value
    """

    coin = coins.pop(0)
    num = 0

    if (chg >= coin):
        num = chg // coin

    rem_chg = chg - (num * coin)

    if rem_chg == 0:
        return num
    else:
        return num + find_change(rem_chg, coins)

print(find_change(int(change * 100)))
