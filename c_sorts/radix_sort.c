#include "radix_sort.h"
#include <stdio.h>
#include <limits.h>
#include <math.h>

int *radix_sort(int *kv_arr, size_t n)
{

    // Guard the trivial case
    if (n == 0) { return kv_arr; }

    // Explode the key into a key tuple with the length corresponding to the digits
    // To do this we create an array that holds pointers to the exploded key which we use bucket struct from buckets to represent
    key_bucket *key_arr = malloc(sizeof(key_bucket) * n);

    int key_digits = _explode_key_seq(kv_arr, key_arr, n);

    // Now use bucket sort starting from LSB iteratively
    for (int i = 0; i < key_digits; i++)
    {
        key_arr = bucket_sort(key_arr, n, 10, i);
    }

    // Now we compact the keys down again
    return _compact_key_seq(kv_arr, n, key_arr, key_digits);
}


int *_compact_key_seq(int *kv_arr, size_t n, key_bucket *key_arr, int key_digits)
{
    // For each entry in the sorted key_arr we need to read through
    // And combine the digits
    for (int i = 0; i < n; i++)
    {
        int combined_key = 0;
        for (int j = 0; j < key_digits; j++)
        {
            combined_key += key_arr[i].arr[j] * pow(10, j);
        }

        // Store in kv_arr
        kv_arr[i] = combined_key;
    }

    return kv_arr;
}


int _explode_key_seq(int *kv_arr, key_bucket *key_arr, size_t n)
{

    // First find the maximum number in our array, this will determine the size of the key array required
    int arr_max = -INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (kv_arr[i] > arr_max)
        {
            arr_max = kv_arr[i];
        }
    }

    // Get number of digits for this max number
    int key_digits = 0;
    while (arr_max != 0)
    {
        arr_max = arr_max / 10;
        key_digits += 1;
    }

    // Now we can malloc our key_buckets
    // Then for each key we store each digit in a separate entry in the array
    for (int i = 0; i < n; i++)
    {
        key_arr[i].arr = malloc(sizeof(int) * key_digits);
        if (!key_arr[i].arr)
        {
            printf("Could not malloc a key array");
            exit(1);
        }

        // Get the current key
        // Store it in the arr in big-endian format
        int cur_key = kv_arr[i];
        for (int j = key_digits - 1; j >= 0; j--)
        {
            int f = pow(10, j);
            if (f > cur_key)
            {
                key_arr[i].arr[j] = 0;

            } else {
                key_arr[i].arr[j] = cur_key / f;
            }
            cur_key = cur_key % f;
        }
    }

    return key_digits;
}


void bucket_append(bucket *bucket, key_bucket kv)
{
    // First create a new node from the values
    _node *node = malloc(sizeof(_node));
    node->value = kv;
    node->next = NULL;

    // Now we insert it into our linked list at the right place
    // We do this in 4 steps:
    // 1. Check if head/tail node is null, if so update to point at the node and done.
    // 2. If not null, get the current tail node
    // 3. Update the next reference in the current tail node to point at the new node
    // 4. Update the tail reference in the bucket to point at the new node
    if ((!bucket->head) & (!bucket->tail))
    {
        bucket->head = node;
        bucket->tail = node;
    }
    else
    {
        _node *tail = bucket->tail;
        tail->next = node;
        bucket->tail = node;
    }
    bucket->length += 1;
}


key_bucket *bucket_sort(key_bucket *key_arr, size_t n, int n_buckets, int key_idx)
{
    // Create our bucket
    bucket buckets[n_buckets];

    // For each bucket go ahead and initialise the struct
    for (int i = 0; i < n_buckets; i++)
    {
        buckets[i].length = 0;
        buckets[i].head = NULL;
        buckets[i].tail = NULL;
    }

    // Now we loop through our array and build the buckets
    for (int i = 0; i < n; i++)
    {
        bucket_append(&buckets[key_arr[i].arr[key_idx]], key_arr[i]);
    }

    // Now we read each bucket in ascending order and concat them all
    // to make the output
    int idx = 0;
    for (int i = 0; i < n_buckets; i++)
    {
        // If head is not null
        if (buckets[i].head)
        {
            // Iteratively traverse the linked list
            _node *node = buckets[i].head;
            while (node)
            {
                key_arr[idx] = node->value;
                node = node->next;
                idx += 1;

            }
        }
    }

    return key_arr;  

}