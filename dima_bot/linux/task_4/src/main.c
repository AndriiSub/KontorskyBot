#include <stdio.h>
#include "arraylist.h"

int main() {
    ArrayList list;
    initArrayList(&list);

    add(&list, 10);
    add(&list, 20);
    add(&list, 30);
    printf("Size of the list: %d\n", size(&list));

    insert(&list, 1, 15);
    printf("Size of the list after insertion: %d\n", size(&list));

    set(&list, 0, 5);
    printf("Value at index 0: %d\n", get(&list, 0));

    removeAt(&list, 2);
    printf("Size of the list after removal: %d\n", size(&list));

    freeArrayList(&list);

    return 0;
}

