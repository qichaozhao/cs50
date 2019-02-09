from cs50 import get_string
from sys import argv, exit


def main():

    if len(argv) != 2:
        exit("Usage: python bleep.py banned_words.txt")

    # Load the banned words into a set
    try:
        with open(argv[1], 'r') as f_in:
            banned = set([l.rstrip("\n") for l in f_in.readlines()])

    except FileNotFoundError:
        exit("Usage: python bleep.py banned_words.txt")

    # Prompt the user for a string
    while True:

        ipt = get_string("What message would you like to censor?\n")

        if ipt != "":
            break

    # Tokenize the input string using spaces
    tkn_ipt = ipt.split(" ")

    # Loop through the tokenized input to create the corresponding output
    out = []
    for tkn in tkn_ipt:

        word = tkn
        if tkn in banned:
            word = "*" * len(tkn)

        out.append(word)

    # Now print the output
    print(" ".join(out))


if __name__ == "__main__":
    main()
