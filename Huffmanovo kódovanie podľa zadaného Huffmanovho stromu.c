#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>  // Для роботи з wchar_t
#include <string.h>

// Структура для вузла дерева
typedef struct Node {
    wchar_t character;
    int frequency;
    struct Node *left, *right;
} Node;

// Функція для створення нового вузла дерева
Node* newNode(wchar_t character, int frequency) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// Функція для створення дерева Хаффмана
void printCodes(Node *root, wchar_t *code, int top) {
    // Якщо це листок (символ)
    if (root->left == NULL && root->right == NULL) {
        code[top] = L'\0';
        wprintf(L"%lc: %ls\n", root->character, code);
        return;
    }

    // Якщо лівий піддерево не порожнє, йдемо в ліве піддерево (додаємо 0)
    if (root->left != NULL) {
        code[top] = L'0';
        printCodes(root->left, code, top + 1);
    }

    // Якщо правий піддерево не порожнє, йдемо в праве піддерево (додаємо 1)
    if (root->right != NULL) {
        code[top] = L'1';
        printCodes(root->right, code, top + 1);
    }
}

// Функція для кодування рядка за допомогою дерева Хаффмана
void encode(Node *root, const wchar_t *input) {
    wchar_t code[100];
    for (int i = 0; i < wcslen(input); i++) {
        Node *current = root;
        wchar_t ch = input[i];

        // Проходимо по дереву для кожного символу
        while (current->left != NULL || current->right != NULL) {
            if (ch < current->character) {
                wprintf(L"0");
                current = current->left;
            } else {
                wprintf(L"1");
                current = current->right;
            }
        }
    }
}

// Функція для створення дерева Хаффмана з заданими символами та їх частотами
Node* buildHuffmanTree() {
    Node *root = newNode(L'\0', 0);
    root->left = newNode(L'a', 5);  // 'a' має частоту 5
    root->right = newNode(L'\0', 0);
    root->right->left = newNode(L'b', 3);  // 'b' має частоту 3
    root->right->right = newNode(L'с', 2);  // 'с' має частоту 2 (кириличний символ)
    return root;
}

int main() {
    // Створюємо дерево Хаффмана для символів 'a', 'b', 'с' (кириличний символ)
    Node *root = buildHuffmanTree();

    // Масив для зберігання коду
    wchar_t code[100];

    // Виводимо коди для кожного символу
    wprintf(L"Huffman Codes:\n");
    printCodes(root, code, 0);

    // Кодування рядка за допомогою дерева Хаффмана
    const wchar_t *input = L"c";  // кириличний символ
    wprintf(L"\nEncoded string: ");
    encode(root, input);
    wprintf(L"\n");

    return 0;
}
