from math import log2, ceil

def merge_sort_nr(arr):
    """
    Implement a non-recursive version of merge sort, that works from the bottom up.

    1. Given an array of elements, merge successive elements into sorted runs of length two
    2. Then merge these runs into length 4, then 8 etc until the array is sorted

    :param arr:
    :return:
    """

    # Guard against the trivial case
    if len(arr) == 0:
        return arr

    # Instantiate our two temporary arrays to hold values
    src, dst = arr, [None] * len(arr)
    logn = int(ceil(log2(len(arr))))

    # Loop through each level of the merge tree
    # Extract the indices for our runs
    for i in (2**k for k in range(logn)):

        # Calculate the window (with a minimum window of 2)
        window = i * 2

        for j in range(0, len(arr), window):
            merge(src, dst, window, j)

        # Swap the arrays so we can write back and forth and save memory
        src, dst = dst, src

    # Since we always do two swaps (as we loop over 2**k), the final output will always be the src variable
    return src


def merge(src, dst, wdw, j):
    """
    Helper function to perform the merges, we rely on the side effect here

    :param arr1:
    :param arr2:
    :return:
    """

    r1_idx = j
    r2_idx = min(j + wdw // 2, len(src))

    end1_idx = min(r1_idx + wdw // 2, len(src))
    end2_idx = min(r2_idx + wdw // 2, len(src))

    write_idx = r1_idx

    # Keep merging until we have exhausted both parts of our run
    while r1_idx < end1_idx or r2_idx < end2_idx:

        if r2_idx == end2_idx or (r1_idx < end1_idx and src[r1_idx] < src[r2_idx]):
            dst[write_idx] = src[r1_idx]
            r1_idx += 1
        else:
            dst[write_idx] = src[r2_idx]
            r2_idx += 1

        write_idx += 1
