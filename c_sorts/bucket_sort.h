#include <stdlib.h>

// We will store our buckets as a singly linked list 
// with head + tail pointers
// tail needed for fast appends
// head needed for fast reads
typedef struct __node {
    int value;
    struct __node *next;
} _node;

typedef struct {
	int length;
    _node *head;
    _node *tail;
} bucket;

int *bucket_sort(int *kv_arr, size_t n, int n_buckets);
void bucket_append(bucket *bucket, int kv);