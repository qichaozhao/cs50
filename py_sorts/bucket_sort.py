def bucket_sort(kv_arr, n_buckets):
    """
    If we have a sequence of (key, value1, value2, ...) tuples where keys are integers in a known range,
    we have a faster algorithm we can use.

    1. For each entry in our sequence, remove from sequence and insert at the end of bucket[key]
    2. Read each bucket sequentially and insert in the original sequence

    :param kv_arr:
    :param n_buckets:
    :return:
    """

    # Instantiate our buckets
    buckets = [[] for i in range(n_buckets)]

    # Build the buckets
    for kv in kv_arr:
        buckets[kv[0]].append(kv)

    idx = 0
    for bucket in buckets:
        for kv in bucket:
            kv_arr[idx] = kv
            idx += 1

    return kv_arr






