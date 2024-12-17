#include <stdio.h>
#include <stdlib.h>
#define MAX 256

typedef struct Node {
    char symbol;
    int freq;
    struct Node *left, *right;
} Node;

Node *queue[MAX];
int queueSize = 0;

void insert(Node *n) {
    int i = queueSize++;
    while (i > 0 && queue[(i - 1) / 2]->freq > n->freq) queue[i] = queue[(i - 1) / 2], i = (i - 1) / 2;
    queue[i] = n;
}

Node *removeMin() {
    Node *min = queue[0], *tmp;
    queue[0] = queue[--queueSize];
    for (int i = 0, sm; ;) {
        int l = 2 * i + 1, r = 2 * i + 2;
        sm = (l < queueSize && queue[l]->freq < queue[i]->freq) ? l : i;
        if (r < queueSize && queue[r]->freq < queue[sm]->freq) sm = r;
        if (sm == i) break;
        tmp = queue[i], queue[i] = queue[sm], queue[sm] = tmp, i = sm;
    }
    return min;
}

Node *newNode(char sym, int freq, Node *l, Node *r) {
    Node *n = malloc(sizeof(Node));
    return n->symbol = sym, n->freq = freq, n->left = l, n->right = r, n;
}

Node *buildHuffmanTree(int freq[]) {
    for (int i = 0; i < MAX; i++) if (freq[i]) insert(newNode(i, freq[i], NULL, NULL));
    while (queueSize > 1) {
        Node *l = removeMin(), *r = removeMin();
        insert(newNode('\0', l->freq + r->freq, l, r));
    }
    return queueSize ? removeMin() : NULL;
}

void printCodes(Node *root, char *code, int depth) {
    if (!root->left && !root->right) {
        code[depth] = '\0';
        if (root->symbol == ' ')
            printf("[space]: %s\n", code);
        else
            printf("%c: %s\n", root->symbol, code);
    } else {
        if (root->left) code[depth] = '0', printCodes(root->left, code, depth + 1);
        if (root->right) code[depth] = '1', printCodes(root->right, code, depth + 1);
    }
}


int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) return 1;
    int freq[MAX] = {0};
    for (char ch; (ch = fgetc(file)) != EOF;) freq[(unsigned char)ch]++;
    fclose(file);
    Node *root = buildHuffmanTree(freq);
    if (!root) return 1;
    char code[MAX];
    printCodes(root, code, 0);
    return 0;
}
