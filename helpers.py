def lines(a, b):
    """Return lines in both a and b"""

    b_lines = b.split("\n")
    return [l for l in a.split("\n") if l in b_lines]


def sentences(a, b):
    """Return sentences in both a and b"""

    from nltk.tokenize import sent_tokenize

    b_sents = sent_tokenize(b)

    return set([w for w in sent_tokenize(a) if w in b_sents])


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    a_substr = set()
    for i in range(0, len(a) - n + 1):
        a_substr.add(a[i:i + n])

    return set([ss for ss in a_substr if ss in b])
