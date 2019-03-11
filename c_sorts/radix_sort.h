#include <stdlib.h>

typedef struct {
	int size;
	int *arr;
} key_bucket;

int _explode_key_seq(int *kv_arr, key_bucket *key_arr, size_t n);
int *_compact_key_seq(int *kv_arr, size_t n, key_bucket *key_arr, int key_digits);
int *radix_sort(int *kv_arr, size_t n);

// Radix sort depends on a slightly altered bucket sort
// We will store our buckets as a singly linked list 
// with head + tail pointers
// tail needed for fast appends
// head needed for fast reads
typedef struct __node {
    key_bucket value;
    struct __node *next;
} _node;

typedef struct {
	int length;
    _node *head;
    _node *tail;
} bucket;

key_bucket *bucket_sort(key_bucket *key_arr, size_t n, int n_buckets, int key_idx);
void bucket_append(bucket *bucket, key_bucket kv);