def merge_sort(arr):
    """
    Implements the recursive merge sort algorithm:

    1. If array has >= 2 elements, split the arr as evenly as possible
    2. Perform merge sort on the child elements
    3. Merge the results into a sorted list

    :return:
    """

    if len(arr) in {0, 1}:
        return arr

    else:
        # Split the array into two
        pivot = len(arr) // 2

        arr1 = [arr[k] for k in range(0, pivot)]
        arr2 = [arr[k] for k in range(pivot, len(arr))]

        return merge(merge_sort(arr1), merge_sort(arr2))


def merge(arr1, arr2):
    """
    Helper function that merges two (sorted) arrays by iterating over them at the same time and popping the minimum
    element at the head of either array to the output array

    :param arr1:
    :param arr2:
    :return:
    """

    out = []
    i = j = 0

    # Now merge
    while (i + j) < len(arr1) + len(arr2):

        if j == len(arr2) or (i < len(arr1) and arr1[i] < arr2[j]):
            out.append(arr1[i])
            i += 1
        else:
            out.append(arr2[j])
            j += 1

    return out