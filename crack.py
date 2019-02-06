from sys import argv, exit
from brute_force import brute_force

if len(argv) != 2:
    exit("Usage: python crack.py hash")

in_hash = argv[1]
char_list = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"


# Generator for the next password
def password_generator(n=5):
    """
    Yields the next password for all combinations up to and including length n
    """
    pwd = [" "] * n
    pwd_idx = [0] * n
    while pwd != "ZZZZZ":
        for i in range(0, n):

            if pwd_idx[i] == 51:
                pwd_idx[i] = (pwd_idx[i] + 1) % 52
                pwd[i] = char_list[pwd_idx[i]]
                yield "".join(pwd).strip(" ")

            else:
                pwd[i] = char_list[pwd_idx[i]]
                pwd_idx[i] += 1
                yield "".join(pwd).strip(" ")
                break


def main():
    for pwd in password_generator():
        res = brute_force(pwd, in_hash)

        if res[0] is True:
            print(res[1])
            exit(0)


if __name__ == "__main__":
    main()
