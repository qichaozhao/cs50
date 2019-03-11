"""
This file contains a wrapper around our C libraries using ctypes
"""

from ctypes import *


class c_sorts(object):
    def __init__(self, include_path="/Users/qzhao/cs50/qichaozhao/c_sorts"):
        self.lib_trivial_sorts = CDLL(f"{include_path}/trivial_sorts.so")
        self.lib_merge_sort = CDLL(f"{include_path}/merge_sort.so")
        self.lib_quick_sort = CDLL(f"{include_path}/quick_sort.so")
        self.lib_bucket_sort = CDLL(f"{include_path}/bucket_sort.so")
        self.lib_radix_sort = CDLL(f"{include_path}/radix_sort.so")

    def insertion_sort(self, arr):
        """
        Insertion sort wrapper

        :param arr:
        :return:
        """

        # Setup the array as a C style array
        n = len(arr)
        c_arr = (c_int * n)(*arr)

        # Declare the return type as a pointer to array of ints
        self.lib_trivial_sorts.insertion_sort.restype = POINTER(c_int)

        # Do the sort, and then return a python list of sorted elements
        w = self.lib_trivial_sorts.insertion_sort(c_arr, n)
        return [w[i] for i in range(n)]

    def selection_sort(self, arr):
        """
        Selection sort wrapper

        :param arr:
        :return:
        """

        # Setup the array as a C style array
        n = len(arr)
        c_arr = (c_int * n)(*arr)

        # Declare the return type as a pointer to array of ints
        self.lib_trivial_sorts.selection_sort.restype = POINTER(c_int)

        # Do the sort, and then return a python list of sorted elements
        w = self.lib_trivial_sorts.selection_sort(c_arr, n)
        return [w[i] for i in range(n)]

    def bubble_sort(self, arr):
        """
        Bubble sort wrapper

        :param arr:
        :return:
        """

        # Setup the array as a C style array
        n = len(arr)
        c_arr = (c_int * n)(*arr)

        # Declare the return type as a pointer to array of ints
        self.lib_trivial_sorts.bubble_sort.restype = POINTER(c_int)

        # Do the sort, and then return a python list of sorted elements
        w = self.lib_trivial_sorts.bubble_sort(c_arr, n)
        return [w[i] for i in range(n)]

    def merge_sort(self, arr):
        """
        Merge sort using C's merge sort function

        :param arr:
        :return:
        """

        # Setup the array as a C style array
        n = len(arr)
        c_arr = (c_int * n)(*arr)

        # Declare the return type as a pointer to array of ints
        self.lib_merge_sort.merge_sort.restype = POINTER(c_int)

        # Do the sort, and then return a python list of sorted elements
        w = self.lib_merge_sort.merge_sort(c_arr, n)
        return [w[i] for i in range(n)]

    def quick_sort(self, arr):
        """
        Merge sort using C's merge sort function

        :param arr:
        :return:
        """

        # Setup the array as a C style array
        n = len(arr)
        c_arr = (c_int * n)(*arr)

        # Declare the return type as a pointer to array of ints
        self.lib_quick_sort.quick_sort.restype = POINTER(c_int)

        # Do the sort, and then return a python list of sorted elements
        w = self.lib_quick_sort.quick_sort(c_arr, n)
        return [w[i] for i in range(n)]

    def bucket_sort(self, arr):
        """
        Bucket sort using C's bucket sort function

        :param arr:
        :return:
        """
        # Setup the array as a C style array
        n = len(arr)
        n_buckets = max(arr) + 1
        c_arr = (c_int * n)(*arr)

        # Declare the return type as a pointer to array of ints
        self.lib_bucket_sort.bucket_sort.restype = POINTER(c_int)

        # Do the sort, and then return a python list of sorted elements
        w = self.lib_bucket_sort.bucket_sort(c_arr, n, n_buckets)
        return [w[i] for i in range(n)]

    def radix_sort(self, arr):
        """
        Radix sort using C's radix sort function

        :param arr:
        :return:
        """
        # Setup the array as a C style array
        n = len(arr)
        c_arr = (c_int * n)(*arr)

        # Declare the return type as a pointer to array of ints
        self.lib_radix_sort.radix_sort.restype = POINTER(c_int)

        # Do the sort, and then return a python list of sorted elements
        w = self.lib_radix_sort.radix_sort(c_arr, n)
        return [w[i] for i in range(n)]
