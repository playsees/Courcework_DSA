#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char sub[100];
    int ch[100];
    int ch_size;
};

struct SuffixTree {
    struct Node nodes[100];
    int nodes_size;
};

void addSuffix(struct SuffixTree* tree, const char* suf) {
    int n = 0;
    int i = 0;
    while (i < strlen(suf)) {
        char b = suf[i];
        int x2 = 0;
        int n2;
        while (1) {
            int* children = tree->nodes[n].ch;
            int children_size = tree->nodes[n].ch_size;
            if (x2 == children_size) {
                n2 = tree->nodes_size;
                strcpy(tree->nodes[n2].sub, suf + i);
                tree->nodes[n2].ch_size = 0;
                children[children_size] = n2;
                tree->nodes[n].ch_size++;
                return;
            }
            n2 = children[x2];
            if (tree->nodes[n2].sub[0] == b) {
                break;
            }
            x2++;
        }
        char* sub2 = tree->nodes[n2].sub;
        int j = 0;
        while (j < strlen(sub2)) {
            if (suf[i + j] != sub2[j]) {
                int n3 = n2;
                n2 = tree->nodes_size;
                strncpy(tree->nodes[n2].sub, sub2, j);
                tree->nodes[n2].sub[j] = '\0';
                tree->nodes[n2].ch_size = 1;
                tree->nodes[n2].ch[0] = n3;
                tree->nodes[n3].sub[0] = '\0';
                tree->nodes[n].ch[x2] = n2;
                break;
            }
            j++;
        }
        i += j;
        n = n2;
    }
}

void visualize(struct SuffixTree* tree, int n, const char* pre) {
    int* children = tree->nodes[n].ch;
    int children_size = tree->nodes[n].ch_size;
    if (children_size == 0) {
        printf("- %s\n", tree->nodes[n].sub);
        return;
    }
    printf("+ %s\n", tree->nodes[n].sub);
    int i;
    for (i = 0; i < children_size - 1; i++) {
        printf("%s+-", pre);
        visualize(tree, children[i], strcat(strdup(pre), "| "));
    }
    printf("%s+-", pre);
    visualize(tree, children[children_size - 1], strcat(strdup(pre), "  "));
}

int main() {
    struct SuffixTree tree;
    strcpy(tree.nodes[0].sub, "");
    tree.nodes[0].ch_size = 0;
    tree.nodes_size = 1;
    addSuffix(&tree, "banana$");
    visualize(&tree, 0, "");
    return 0;
}


