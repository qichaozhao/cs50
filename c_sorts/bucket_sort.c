#include "bucket_sort.h"
#include <stdio.h>

// This bucket sort works for 1d arrays
// We go a little bit restrictive compared to python
int *bucket_sort(int *kv_arr, size_t n, int n_buckets)
{

    // Guard against the trivial case
    if (n == 0) { return kv_arr; }

    // The number of buckets should be the maximum integer value in the list + 1

    // Create our buckets
    bucket buckets[n_buckets];

    // For each bucket go ahead and initialise the struct
    for (int i = 0; i < n_buckets; i++)
    {
        buckets[i].length = 0;
        buckets[i].head = NULL;
        buckets[i].tail = NULL;
    }

    // Now we loop through our array and build the buckets
    for (int i = 0; i < n; i ++)
    {
        bucket_append(&buckets[kv_arr[i]], kv_arr[i]);
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
                kv_arr[idx] = node->value;
                node = node->next;
                idx += 1;
            }
        }
    }

    return kv_arr;
}

void bucket_append(bucket *bucket, int kv)
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
