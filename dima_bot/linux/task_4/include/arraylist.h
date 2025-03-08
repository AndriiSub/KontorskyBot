#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct {
    int *data;
    int size;
    int capacity;
} ArrayList;

void initArrayList(ArrayList *list);
void add(ArrayList *list, int item);
void insert(ArrayList *list, int index, int item);
int size(const ArrayList *list);
void set(ArrayList *list, int index, int item);
int get(const ArrayList *list, int index);
void removeAt(ArrayList *list, int index);
void freeArrayList(ArrayList *list);

#endif

