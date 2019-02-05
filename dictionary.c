// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

int find_index(const char c);
unsigned int size_rec(struct node *head);
void unload_rec(struct node *head);

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
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

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {

        // Set the current head
        node *head = root;

        // Get the index of the word
        char *c = word;
        while (*c != '\0')
        {
            int idx = find_index(*c);
            node *child = NULL;

            // Create new child node if one does not exist
            // Otherwise use the existing one
            if (head->children[idx] == NULL)
            {
                child = malloc(sizeof(node));
                if (child == NULL)
                {
                    unload();
                    return false;
                }

                // Set the parameters for the child node
                child->is_word = false;
                for (int i = 0; i < N; i++)
                {
                    child->children[i] = NULL;
                }

                // Now add the child to the trie
                head->children[idx] = child;
            }
            else
            {
                child = head->children[idx];
            }

            // Now update the head variable to point to the child
            // so we can keep growing the trie.
            head = child;

            // Increment the pointer
            c++;
        }

        // Now we've looped through the entire word, we should finish off
        // with the word flag
        head->is_word = true;


    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Call our rescursive helper function
    return size_rec(root);
}

unsigned int size_rec(struct node *head)
{
    // Loop through all the branches of the trie and count occurrences of is_word=true
    int count = 0;
    if (head->is_word)
    {
        count++;
    }

    for (int i = 0; i < N; i++)
    {
        if (head->children[i] != NULL)
        {
            count += size_rec(head->children[i]);
        }
    }
    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Lowercase the word
    char lower_word[LENGTH + 1];
    for (int i = 0; i < strlen(word) + 1; i++)
    {
        lower_word[i] = tolower(word[i]);
    }

    // Traverse the trie using the lowercased word
    char *c = lower_word;
    node *head = root;
    while (*c != '\0')
    {
        // Get the index of the child to look at
        // Then traverse to it by setting the head to there
        int idx = find_index(*c);

        if (head->children[idx] != NULL)
        {
            head = head->children[idx];
        }
        else
        {
            return false;
        }

        // Increment the pointer.
        c++;
    }

    // Now we should have traversed the trie to where the word should be
    if (head->is_word == true)
    {
        return true;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // We need to recursively navigate down the trie and free all the alloc'd memory
    unload_rec(root);
    return true;
}

void unload_rec(struct node *head)
{
    // Loop through and free all the children, then free the head
    for (int i = 0; i < N; i++)
    {
        if (head->children[i] != NULL)
        {
            unload_rec(head->children[i]);
        }
    }

    free(head);
}

int find_index(const char c)
{
    if (c == '\'')
    {
        return 26;
    }
    else
    {
        return tolower(c) - 'a';
    }
}
