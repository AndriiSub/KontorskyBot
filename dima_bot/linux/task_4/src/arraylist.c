#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

// Ініціалізація списку
void initArrayList(ArrayList *list) {
    list->size = 0;
    list->capacity = 10;
    list->data = (int *)malloc(list->capacity * sizeof(int));
    if (!list->data) {
        fprintf(stderr, "Помилка виділення пам'яті!\n");
        exit(EXIT_FAILURE);
    }
}

// Додавання елемента в кінець списку
void add(ArrayList *list, int item) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        int *temp = (int *)realloc(list->data, list->capacity * sizeof(int));
        if (!temp) {
            fprintf(stderr, "Помилка перевиділення пам'яті!\n");
            exit(EXIT_FAILURE);
        }
        list->data = temp;
    }
    list->data[list->size++] = item;
}

// Вставка елемента в певну позицію
void insert(ArrayList *list, int index, int item) {
    if (index < 0 || index > list->size) return;

    if (list->size == list->capacity) {
        list->capacity *= 2;
        int *temp = (int *)realloc(list->data, list->capacity * sizeof(int));
        if (!temp) {
            fprintf(stderr, "Помилка перевиділення пам'яті!\n");
            exit(EXIT_FAILURE);
        }
        list->data = temp;
    }

    for (int i = list->size; i > index; --i) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = item;
    list->size++;
}

// Отримання розміру списку
int size(const ArrayList *list) {
    return list->size;
}

// Оновлення елемента в списку
void set(ArrayList *list, int index, int item) {
    if (index >= 0 && index < list->size) {
        list->data[index] = item;
    }
}

// Отримання елемента за індексом
int get(const ArrayList *list, int index) {
    return (index >= 0 && index < list->size) ? list->data[index] : -1;
}

// Видалення елемента за індексом
void removeAt(ArrayList *list, int index) {
    if (index < 0 || index >= list->size) return;

    for (int i = index; i < list->size - 1; ++i) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
}

// Звільнення пам'яті
void freeArrayList(ArrayList *list) {
    free(list->data);
    list->data = NULL;
    list->size = list->capacity = 0;
}