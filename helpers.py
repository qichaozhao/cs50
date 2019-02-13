def lines(a, b):
    """Return lines in both a and b"""

    a_lines = set(a.split("\n"))
    b_lines = set(b.split("\n"))

    return a_lines & b_lines


def sentences(a, b):
    """Return sentences in both a and b"""

    from nltk.tokenize import sent_tokenize

    a_sents = sent_tokenize(a)
    b_sents = sent_tokenize(b)

    return a_sents & b_sents


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    a_substr = set([a[i:i + n] for i in range(0, len(a) - n + 1)])
    b_substr = set([b[i:i + n] for i in range(0, len(b) - n + 1)])

    return a_substr & b_substr
