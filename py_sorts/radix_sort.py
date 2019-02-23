def radix_sort(kv_arr):
    """
    Radix sort starting from the least significant bit. Will return a sorted list as expected (0, 1, 2, 10, 20)
    :return:
    """

    # First explode the key into tuples
    key_digits = _explode_key_seq(kv_arr)

    # Now use bucket sort starting from the LSB iteratively
    for i in reversed(range(key_digits)):
        bucket_sort(kv_arr, 10, i)

    # Now we need to compact the key sequence
    _compact_key_seq(kv_arr)

    return kv_arr


def _compact_key_seq(kv_arr):
    """
    Helper function that compacts the key sequence (used after sorting)

    :param kv_arr:
    :return:
    """

    for i in range(len(kv_arr)):
        key = "".join([str(k) for k in kv_arr[i][0]])
        kv_arr[i][0] = int(key)

    return kv_arr


def _explode_key_seq(kv_arr):
    """
    Helper function that generates the key sequence to feed into the radix sort function

    :param kv_arr:
    :return:
    """

    max_key = max([kv[0] for kv in kv_arr])

    # This is not the most performant solution
    key_digits = len(str(max_key))

    # Replace the key with a tuple containing each digit
    for i in range(len(kv_arr)):
        key_str = str(kv_arr[i][0]).zfill(key_digits)
        kv_arr[i][0] = tuple([int(key_str[i]) for i in range(key_digits)])

    return key_digits


def bucket_sort(kv_arr, n_buckets, key_idx):
    """
    If we have a sequence of (key, value1, value2, ...) tuples where keys are integers in a known range,
    we have a faster algorithm we can use.

    Slightly modified to be able to assist with radix sort by taking a tuple key and sorting by the index of the tuple

    1. For each entry in our sequence, remove from sequence and insert at the end of bucket[key]
    2. Read each bucket sequentially and insert in the original sequence

    :param kv_arr:
    :param n_buckets:
    :param key_idx:
    :return:
    """

    # Instantiate our buckets
    buckets = [[] for i in range(n_buckets)]

    # Build the buckets
    for kv in kv_arr:
        buckets[kv[0][key_idx]].append(kv)

    idx = 0
    for bucket in buckets:
        for kv in bucket:
            kv_arr[idx] = kv
            idx += 1

    return kv_arr
