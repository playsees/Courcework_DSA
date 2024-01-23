#include <stdio.h>        // Подключение заголовочного файла для ввода/вывода
#include <stdlib.h>       // Подключение заголовочного файла для функций общего назначения
#include <string.h>       // Подключение заголовочного файла для работы со строками

// Структура узла суффиксного дерева
struct SuffixTreeNode {
    struct SuffixTreeNode* children[256];  // Массив указателей на потомков (детей) узла, 256 - количество возможных символов в ASCII
    int start;                              // Хранит индекс начала суффикса
    int* end;                               // Хранит указатель на конец суффикса (последний символ)
};

// Создание нового узла суффиксного дерева
struct SuffixTreeNode* createNewNode(int start, int* end) {
    struct SuffixTreeNode* node = (struct SuffixTreeNode*)malloc(sizeof(struct SuffixTreeNode));  // Выделение памяти под новый узел
    for (int i = 0; i < 256; ++i) {
        node->children[i] = NULL;         // Инициализация массива потомков нулевыми указателями
    }
    node->start = start;                   // Установка начала суффикса
    node->end = end;                       // Установка конца суффикса
    return node;                           // Возвращение созданного узла
}

// Вставка суффикса в суффиксное дерево
void insertSuffix(struct SuffixTreeNode* root, char* suffix, int suffixIndex) {
    struct SuffixTreeNode* currentNode = root;  // Начинаем с корневого узла
    for (int i = 0; suffix[i] != '\0'; ++i) {
        if (currentNode->children[(unsigned char)suffix[i]] == NULL) {  // Если у текущего узла нет потомка с таким символом
            int* end = (int*)malloc(sizeof(int));  // Выделяем память под конец суффикса
            *end = suffixIndex + i;                // Устанавливаем значение конца суффикса
            currentNode->children[(unsigned char)suffix[i]] = createNewNode(suffixIndex, end);  // Создаем новый узел и устанавливаем его как потомка
        }
        currentNode = currentNode->children[(unsigned char)suffix[i]];  // Переходим к следующему узлу
    }
}

// Вывод суффиксов, начинающихся с данного узла
void printSuffixes(struct SuffixTreeNode* node, char* originalText) {
    if (node == NULL) {
        return;  // Если узел пустой, выходим из функции
    }

    if (node->start != -1) {
        printf("%.*s\n", *(node->end) - node->start + 1, originalText + node->start);  // Выводим суффикс в консоль
    }

    for (int i = 0; i < 256; ++i) {
        if (node->children[i] != NULL) {
            printSuffixes(node->children[i], originalText);  // Рекурсивно вызываем функцию для каждого потомка
        }
    }
}

// Построение суффиксного дерева для строки
void buildSuffixTree(char* text) {
    int n = strlen(text);                              // Получаем длину строки
    struct SuffixTreeNode* root = createNewNode(-1, NULL);  // Создаем корневой узел суффиксного дерева

    // Вставляем все суффиксы в суффиксное дерево
    for (int i = 0; i < n; ++i) {
        insertSuffix(root, text + i, i);               // Вставляем суффикс, начиная с каждого символа строки
    }

    // Выводим уникальные суффиксы в консоль
    printf("Суффиксы строки:\n");
    printSuffixes(root, text);
}

int main() {
    char text[] = "Banana";  // Исходная строка

    buildSuffixTree(text);    // Вызываем функцию построения суффиксного дерева

    return 0;                 // Возвращаем 0, чтобы показать успешное завершение программы
}

