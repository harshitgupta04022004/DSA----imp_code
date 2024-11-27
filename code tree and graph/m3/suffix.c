#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

/*
 suffix trees are the compressed tries.
*/

typedef struct SuffixTreeNode {
    struct SuffixTreeNode *children[MAX_CHAR];
    struct SuffixTreeNode *suffixLink;
    int start;
    int *end;
    int suffixIndex;
} SuffixTreeNode;

typedef struct SuffixTree {
    SuffixTreeNode *root;
    char *text;
    int length;
    SuffixTreeNode *lastNewNode;
    SuffixTreeNode *activeNode;
    int activeEdge;
    int activeLength;
    int remainingSuffixCount;
    int leafEnd;
    int *rootEnd;
    int *splitEnd;
} SuffixTree;

SuffixTreeNode *newNode(int start, int *end, SuffixTree *tree) {
    SuffixTreeNode *node = (SuffixTreeNode *)malloc(sizeof(SuffixTreeNode));
    for (int i = 0; i < MAX_CHAR; i++)
        node->children[i] = NULL;

    node->suffixLink = tree->root;
    node->start = start;
    node->end = end;
    node->suffixIndex = -1;

    return node;
}

void extendSuffixTree(SuffixTree *tree, int pos) {
    // Code to extend the suffix tree for position 'pos'
    // This function will handle the extension logic for each character addition
}

void buildSuffixTree(SuffixTree *tree, const char *text) {
    tree->length = strlen(text);
    tree->text = (char *)text;
    tree->rootEnd = (int *)malloc(sizeof(int));
    *tree->rootEnd = -1;

    tree->root = newNode(-1, tree->rootEnd, tree);
    tree->activeNode = tree->root;

    for (int i = 0; i < tree->length; i++)
        extendSuffixTree(tree, i);
}

void printSuffixTree(SuffixTreeNode *node, int height, SuffixTree *tree) {
    if (node == NULL) return;

    if (node->start != -1) {
        for (int i = node->start; i <= *(node->end); i++)
            printf("%c", tree->text[i]);
    }
    printf(" [%d]\n", node->suffixIndex);

    for (int i = 0; i < MAX_CHAR; i++) {
        if (node->children[i] != NULL) {
            if (node->suffixIndex == -1)
                printSuffixTree(node->children[i], height + 1, tree);
        }
    }
}

int main() {
    const char *text = "banana$";
    SuffixTree tree;
    buildSuffixTree(&tree, text);
    printSuffixTree(tree.root, 0, &tree);
    return 0;
}
