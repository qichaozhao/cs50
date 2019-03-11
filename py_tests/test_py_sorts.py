"""
Testing for sorts
"""
import random
import sys

sys.path.insert(0, '../')
from py_sorts import insertion_sort, selection_sort, bubble_sort, \
    merge_sort, merge_sort_nr, \
    quick_sort, quick_sort_ip, \
    bucket_sort, radix_sort

INT_INPUTS = [
    [],
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
    random.sample(list(range(0, 100)), 100),
    random.sample(list(range(0, -100, -1)), 100),
    random.sample(list(range(0, 151)), 151)
]

INT_OUTPUTS = [
    [],
    list(range(0, 11)),
    list(range(0, 100)),
    list(range(-99, 1, 1)),
    list(range(0, 151))
]


def test_insertion_sort():
    for ipt, opt in zip(INT_INPUTS, INT_OUTPUTS):
        assert (insertion_sort(ipt.copy()) == opt)


def test_selection_sort():
    for ipt, opt in zip(INT_INPUTS, INT_OUTPUTS):
        assert (selection_sort(ipt.copy()) == opt)


def test_bubble_sort():
    for ipt, opt in zip(INT_INPUTS, INT_OUTPUTS):
        assert (bubble_sort(ipt.copy()) == opt)


def test_merge_sort():
    for ipt, opt in zip(INT_INPUTS, INT_OUTPUTS):
        assert (merge_sort(ipt.copy()) == opt)


def test_merge_sort_nr():
    for ipt, opt in zip(INT_INPUTS, INT_OUTPUTS):
        assert (merge_sort_nr(ipt.copy()) == opt)


def test_quick_sort():
    for ipt, opt in zip(INT_INPUTS, INT_OUTPUTS):
        assert (quick_sort(ipt.copy()) == opt)


def test_quick_sort_ip():
    for ipt, opt in zip(INT_INPUTS, INT_OUTPUTS):
        assert (quick_sort_ip(ipt.copy()) == opt)


def test_bucket_sort():
    for ipt, opt in zip(INT_INPUTS, INT_OUTPUTS):
        # Modify the inputs to make them into lists
        # Also remove negative inputs as bucket sort deals with positive integer keys only
        if sum(i < 0 for i in ipt.copy()) > 0:
            continue

        subs_ipt = [[i, i] for i in ipt.copy()]
        subs_opt = [[o, o] for o in opt]
        assert (bucket_sort(subs_ipt, len(subs_ipt)) == subs_opt)

    for ipt, opt in zip(INT_INPUTS, INT_OUTPUTS):
        if sum(i < 0 for i in ipt.copy()) > 0:
            continue

        assert (bucket_sort(ipt.copy(), len(ipt)) == opt)


def test_radix_sort():
    for ipt, opt in zip(INT_OUTPUTS, INT_OUTPUTS):
        # Modify the inputs to make them into lists
        # Also remove negative inputs as radix sort relies on bucket sort which works for +ve integer keys only
        if sum(i < 0 for i in ipt.copy()) > 0:
            continue

        subs_ipt = [[i, i] for i in ipt.copy()]
        subs_opt = [[o, o] for o in opt]
        assert (radix_sort(subs_ipt.copy()) == subs_opt)

    for ipt, opt in zip(INT_INPUTS, INT_OUTPUTS):
        if sum(i < 0 for i in ipt.copy()) > 0:
            continue

        assert (radix_sort(ipt.copy()) == opt)
