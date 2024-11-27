#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEVEL 6



/*
A skip list is a data structure that allows for fast search, insertion, and deletion operations, similar to a balanced tree. It consists of multiple layers where each layer is a subset of the previous one, allowing for logarithmic time complexity for average cases of various operations.

we make a sentinal node and to that has all the level (6) in the level L1 we make the skip list from the L0 node randomly select the perticular node level of the node and connect the node with the sentinal node and the privious nodes accordingly that have different level L0.
similarly do this for the other levels L2 select the node from the L1 and build that level continue this process till level  6

while insertion of the node make the node and randomly select the number of levels of that node [eg:4] and connect the code in the correct postion and and connect  the level from the previous node and the next node  accordingly



*/

typedef struct Node {
    int key;
    struct Node *forward[MAX_LEVEL + 1];
} Node;

typedef struct SkipList {
    int level;
    Node *header;
} SkipList;


Node* createNode(int level, int key) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->key = key;
    for (int i = 0; i <= level; i++) {
        n->forward[i] = NULL;
    }
    return n;
}


SkipList* createSkipList() {
    SkipList *sl = (SkipList *)malloc(sizeof(SkipList));
    sl->level = 0;
    sl->header = createNode(MAX_LEVEL, INT_MIN);
    return sl;
}


int randomLevel() {
    int level = 0;
    while (rand() < RAND_MAX/2 && level < MAX_LEVEL)
        level++;
    return level;
}



void insert(SkipList *sl, int key) {
    Node *current = sl->header;
    Node *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(Node*) * (MAX_LEVEL + 1));

    for (int i = sl->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }

    current = current->forward[0];
    if (current == NULL || current->key != key) {
        int rlevel = randomLevel();
        if (rlevel > sl->level) {
            for (int i = sl->level + 1; i <= rlevel; i++)
                update[i] = sl->header;
            sl->level = rlevel;
        }

        Node *n = createNode(rlevel, key);
        for (int i = 0; i <= rlevel; i++) {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
    }
}



int search(SkipList *sl, int key) {
    Node *current = sl->header;
    for (int i = sl->level; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key)
            current = current->forward[i];
            
    }

    current = current->forward[0];
    if (current && current->key == key) {
        return 1;
    }
    return 0;
}



int main() {
    SkipList *sl = createSkipList();
    insert(sl, 3);
    insert(sl, 6);
    insert(sl, 7);
    insert(sl, 9);
    insert(sl, 12);
    insert(sl, 19);
    insert(sl, 17);

    printf("Search for 6: %d\n", search(sl, 6));
    printf("Search for 19: %d\n", search(sl, 19));

    return 0;
}
