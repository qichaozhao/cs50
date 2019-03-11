def quick_sort_ip_rec(arr, a, b):
    """
    A more efficient implementation of quick sort that uses less memory because all the operations are done in place.

    :param arr:
    :return:
    """

    # Initialise some of the vars we will use
    l = a
    r = b

    # Guard against the trivial case
    if l >= r: return

    # Find the pivot and swap with the last value in the list
    p = (r + l) // 2
    pivot = arr[p]
    arr[p], arr[r] = arr[r], arr[p]
    p = r

    # Decrement the right index so we exclude the pivot from comparisons
    r -= 1

    # Scan and swap elements to create the sublists
    while l <= r:

        # Increment l until we find the first value that needs to be swapped
        while l <= r and arr[l] < pivot:
            l += 1

        # Decrement r until we find the first value that needs to be swapped
        while l <= r and arr[r] > pivot:
            r -= 1

        # Make the swap and shrink the range
        if l <= r:
            arr[l], arr[r] = arr[r], arr[l]
            l += 1
            r -= 1

    # Move the pivot to the correct place
    arr[p], arr[l] = arr[l], arr[p]

    # Now we can recurse
    quick_sort_ip_rec(arr, a, l - 1)
    quick_sort_ip_rec(arr, l + 1, b)

def quick_sort_ip(arr):
    """
    The wrapper for quick sort recursive functino

    :param arr:
    :return:
    """
    quick_sort_ip_rec(arr, 0, len(arr) - 1)
    return arr

