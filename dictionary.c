// https://cs50.harvard.edu/x/2020/psets/5/speller/

// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * 26 * 26 * 26;

// Hash table (alphabet char * alphabet char + apostrophe/empty char that goes to same bucket as 'a')
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int i = hash(word);

    for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number (sort alphabetically by first three letters)
unsigned int hash(const char *word)
{
    // First letter value
    unsigned int h1 = tolower(word[0]) % 97;
    unsigned int h2 = 0;
    unsigned int h3 = 0;
    unsigned int h4 = 0;

    //printf("%lu\n", strlen(word));
    //printf("char 2: %c\n", word[1]);
    //printf("char 3: %c\n", word[2]);

    if (strlen(word) > 1 && isalpha(word[1]))
    {
        h2 = tolower(word[1]) % 97;
        //printf("2YES\n");
    }

    if (strlen(word) > 2 && isalpha(word[2]))
    {
        h3 = tolower(word[2]) % 97;
        //printf("3YES\n");
    }

    if (strlen(word) > 3 && isalpha(word[2]))
    {
        h4 = tolower(word[3]) % 97;
    }


    // Return index
    return (h1 * 26) + (h2 * 26) + (h3 * 26) + h4;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Load each word into buffer
    char buffer[LENGTH + 2];

    while (fgets(buffer, LENGTH + 2, dict))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        unsigned int index = hash(buffer);

        // Create node and check if there is enough memory for it
        node *w = malloc(sizeof(node));

        if (w == NULL)
        {
            return false;
        }

        // Copy word from buffer to the node, then insert the node in the hash table
        strcpy(w->word, buffer);
        w->next = NULL;

        if (table[index] == NULL)
        {
            table[index] = w;
        }

        else
        {
            w->next = table[index];
            table[index] = w;
        }
    }

    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int word_counter = 0;

    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            word_counter++;
        }
    }

    return word_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    return true;
}
