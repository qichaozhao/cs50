// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"


// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table (or linked list)
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Function prototype for linked list node deletion
void ll_delete(struct node *node_ptr);

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // First let's hash the word
        int idx = hash(word);

        // Now malloc the wordnode
        node *wordnode = malloc(sizeof(node));
        memcpy(wordnode->word, word, sizeof(word));
        wordnode->next = NULL;

        // Now check the contents at the location of the hashtable
        // If null, then we create the first linked list and insert it
        // Else a list already exists so we have to append to the existing linkedlist
        if (hashtable[idx] == NULL)
        {
            hashtable[idx] = wordnode;
        }
        else
        {
            // First set the new wordnode to point to the first node of the existing linked list
            wordnode->next = hashtable[idx];

            // Now change the stored reference to point to the wordnode
            hashtable[idx] = wordnode;
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i] != NULL)
        {
            // Count the length of the linked list by traversing it
            struct node *head = hashtable[i];
            while (head != NULL)
            {
                head = head->next;
                count++;
            }
        }

    }
    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash the word to find the index
    int idx = hash(word);

    // Now let's move everything to lower case
    char lower_word[LENGTH + 1];
    for (int i = 0; word[i]; i++)
    {
        lower_word[i] = tolower(word[i]);
    }

    // Now traverse the linked list to check if the word exists
    if (hashtable[idx] != NULL)
    {
        struct node *head = hashtable[idx];
        while (head != NULL)
        {
            if (strcmp(head->word, lower_word) == 0)
            {
                return true;
            }
            head = head->next;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (hashtable[i] != NULL)
        {
            ll_delete(hashtable[i]);
            hashtable[i] = NULL;
        }

    }
    return true;
}

// Recursively traverse the node and delete
void ll_delete(struct node *head)
{
    if (head == NULL)
    {
        return;
    }

    ll_delete(head->next);
    free(head);
}

