"""
Implement trivial sorting methods here.
"""
import sys

def insertion_sort(arr):
    """
    Implements the insertion sort algorithm.

    1. Consider each element in the array.
    2. If element k is smaller than element k - 1, then move it backwards until no longer true

    :param desc:
    :return:
    """

    for idx in range(0, len(arr)):

        cur_value = arr[idx]
        insert_idx = idx - 1

        while (insert_idx >= 0 and arr[insert_idx] > cur_value):
            arr[insert_idx + 1], arr[insert_idx] = arr[insert_idx], cur_value
            insert_idx -= 1

    return arr

def selection_sort(arr):
    """
    Implements the selection sort algorithm

    1. Consider each element in the array of length n
    2. Find the minimum value between index k and n and set index k equal to this value

    :param arr:
    :return:
    """

    for idx in range(0, len(arr)):

        # Scan the list tail for the current minimum value
        mv = sys.maxsize
        mv_idx = 0
        for j in range(idx, len(arr)):
            if arr[j] < mv:
                mv = arr[j]
                mv_idx = j

        # Swap the minimum value with the current value
        arr[idx], arr[mv_idx] = arr[mv_idx], arr[idx]

    return arr


def bubble_sort(arr):
    """
    Implements the bubble sort algorithm

    1. Consider a "bubble" of two elements (k, k+1)
    2. If k+1 < k, then swap the two elements
    3. If a pass happens with no swaps, then the list must be sorted.

    :param arr:
    :return:
    """

    swap_flag = True
    while swap_flag is True:
        swap_flag = False

        for idx in range(0, len(arr) - 1):

            if (arr[idx] > arr[idx + 1]):
                arr[idx], arr[idx + 1] = arr[idx + 1], arr[idx]
                swap_flag = True

    return arr