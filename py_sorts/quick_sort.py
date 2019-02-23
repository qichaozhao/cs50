def quick_sort(arr):
    """
    Implements quicksort

    1. For arrays of length n > 2 pick a pivot value at index p (randomly)
    2. For all values < p place in a new array called L, values = p in a new array called E, values > p in a new array called G
    3. Recursively quick_sort these sub-arrays
    4. Concatenate the results together

    :param arr:
    :return:
    """

    # Guard the trivial case
    if len(arr) < 2:
        return arr

    # Pick the pivot at the midpoint
    # This helps to avoid worst case O(n^2) for partially sorted arrays
    pivot = arr[len(arr) // 2]

    # Divide into 3 sub arrays
    L = []
    E = []
    G = []
    for v in arr:
        if v < pivot:
            L.append(v)
        elif v == pivot:
            E.append(v)
        else:
            G.append(v)

    quick_sort(L)
    quick_sort(G)

    # Concatenate the results using slice assignment
    arr[:len(L)] = L
    arr[len(L):len(L) + len(E)] = E
    arr[len(L) + len(E):] = G

    return arr