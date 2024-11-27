#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26  // Assuming only lowercase letters

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;  // True if the node represents end of a word
} TrieNode;



/*
A Trie, also known as a prefix tree, is a tree-like data structure that proves very efficient for managing strings over an alphabet. 
It is used to store a dynamic set or associative array where the keys are usually strings. 
Tries are particularly useful for tasks like autocomplete in search engines, spell checkers, IP routing , and more.

*/

// Function to create a new trie node
TrieNode *getTrieNode(void) {
    TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));
    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// Function to insert a key in the Trie
void insert(TrieNode *root, const char *key) {
    TrieNode *pCrawl = root;
    int length = strlen(key);
    int index;

    for (int level = 0; level < length; level++) {
        index = key[level] - 'a';  // Convert current character into index
        if (!pCrawl->children[index])
            pCrawl->children[index] = getTrieNode();

        pCrawl = pCrawl->children[index];
    }

    // Mark the last node as leaf (end of word)
    pCrawl->isEndOfWord = true;
}


// Function to search a key in the Trie
bool search(TrieNode *root, const char *key) {
    TrieNode *pCrawl = root;
    int length = strlen(key);
    int index;

    for (int level = 0; level < length; level++) {
        index = key[level] - 'a';

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

// Function to check if there is any word in the Trie that starts with the given prefix
bool startsWith(TrieNode *root, const char *prefix) {
    TrieNode *pCrawl = root;
    int length = strlen(prefix);
    int index;

    for (int level = 0; level < length; level++) {
        index = prefix[level] - 'a';

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return true;
}



int main() {
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    TrieNode *root = getTrieNode();

    // Construct trie
    for (int i = 0; i < sizeof(keys)/sizeof(keys[0]); i++)
        insert(root, keys[i]);

    // Search for different keys
    search(root, "the") ? printf("Yes\n") : printf("No\n");
    search(root, "these") ? printf("Yes\n") : printf("No\n");
    startsWith(root, "th") ? printf("Prefix yes\n") : printf("Prefix no\n");

    return 0;
}

