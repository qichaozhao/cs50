import crypt


def brute_force(pwd, in_hash):
    """
    Invokes the crypt function to check the password against the hash,
    return a tuple (bool, string)
    """
    salt = in_hash[:2]
    new_hash = crypt.crypt(pwd, salt=salt)

    if in_hash == new_hash:
        return (True, pwd)

    return (False, '')
